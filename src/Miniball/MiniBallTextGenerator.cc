/************************************************************************
 * 
 *  handle histogramming using simple ascii files
 * 
 ************************************************************************/


#include "Miniball/MiniBallTextGenerator.hh"

using namespace std;

MiniBallTextHistogram::MiniBallTextHistogram(G4String histo_name, G4int p_bin,
					     G4double p_low, G4double p_high)
  : bin(p_bin), low(p_low), high(p_high), overflow(0), underflow(0), 
    file_written(false)
{
  // try to open outputfile
  G4String file_name = histo_name + HIST_FILE_EXT;

  hist_file.open(file_name.c_str(), ofstream::out);

  if(!hist_file) {
    cerr << "MiniBallTextHistogram: "
	 << "could not open histogram file " << file_name << endl;
    return;
  }

  data = (G4int*)malloc( bin*sizeof(G4int) + 1);

  if(!data) {
    cerr << "MiniBallTextHistogram: "
         << "could not allocate memory for histogram" << endl;
    return;
  }

  if(low>high) {
    G4double tmp = low;
    low=high;
    high=tmp;
  } else if(low==high) {
    cerr << "MiniBallTextHistogram: "
	 << "could not allocate memory for histogram" << endl;
    return;
  }

  bin_size = (high-low)/(bin-1);
  eff_low = low - bin_size/2;
  eff_high = high + bin_size/2;
}

MiniBallTextHistogram::~MiniBallTextHistogram()
{
  if(data && hist_file) {
    if(!file_written)
      Close();
    free(data);
  } else if(hist_file) {
    hist_file << "error: not enough memory" << endl;
    hist_file.close();
  } else if(data)
    free(data);
}

void MiniBallTextHistogram::Close()
{
  if(hist_file && !file_written) {
    // write histogram to file
    for(G4int i=0; i<bin; i++) 
       hist_file << low+((G4double)i)*bin_size << " " << data[i] << endl;
    hist_file.close();
    file_written=true;
  }
}
void MiniBallTextHistogram::Fill(G4double value)
{
  if(!data || !hist_file)
    return;

  // find bin
  if(value < eff_low) {
    underflow++;
    return;
  }
  if(value > eff_high) {
    overflow++;
    return;
  }
  
  value -= eff_low;
  G4int value_bin = (G4int)(value/bin_size);

  if(value_bin<0 || value_bin>=bin) {
    cerr << "MiniBallTextHistogram: unexpected error" << endl;
    return;
  }

  data[value_bin]++;
}

void MiniBallTextHistogram::SetBinContent(G4int insbin, G4double content)
{
  if(!data || !hist_file)
    return;

  if(insbin<0 || insbin>=bin)
    return;

  data[insbin] = (G4int)content;
}

G4double MiniBallTextHistogram::GetBinContent(G4int ret_bin)
{
  if(!data || !hist_file)
    return(0.);

  // find bin
  if(ret_bin<0 || ret_bin>=bin)
    return(0.);

  return(data[ret_bin]);
}

MiniBallTextTuple::MiniBallTextTuple(G4String tuple_name)
  : started_writing(false)
{
  // try to open outputfile
  G4String file_name = tuple_name + TUPLE_FILE_EXT;

  tuple_file.open(file_name.c_str(), ofstream::out);

  if(!tuple_file) {
    cerr << "MiniBallTextHistogram: "
	 << "could not open tuple file " << file_name << endl;
    return;
  }
}

MiniBallTextTuple::~MiniBallTextTuple()
{
  if(tuple_file)
    Close();

  column_values.erase(column_values.begin(), column_values.end());
  column_default.erase(column_default.begin(), column_default.end());
}

void MiniBallTextTuple::Close()
{
  if(tuple_file)
    tuple_file.close();
}

G4int MiniBallTextTuple::AddColumn(G4String field_name, G4double default_value)
{
  if(started_writing) {
    cerr << "MiniBallTextTuple: cannot create new column after "
	 << "started writing data" << endl;
    return(-1);
  }

  tuple_file << field_name << " ";

  column_values.push_back(default_value);
  column_default.push_back(default_value);

  return(column_values.size()-1);
}

void MiniBallTextTuple::FillColumn(G4int column_id, G4double value)
{
  // check if column_id is valid
  if(column_id<0 || column_id>=(G4int)column_values.size())
    return;

  column_values[column_id]=value;
}

void MiniBallTextTuple::Clear()
{
  for(size_t column_id=0; column_id<column_values.size(); column_id++)
     column_values[column_id]=column_default[column_id];
}

void MiniBallTextTuple::Fill()
{
  if(!started_writing) {
    tuple_file << endl;
    started_writing=true;
  }

  for(size_t column_id=0; column_id<column_values.size(); column_id++)
     tuple_file << column_values[column_id] << " ";
  
  tuple_file << endl;
  Clear();
}

MiniBallTextGenerator::MiniBallTextGenerator()
{
}

MiniBallTextGenerator::~MiniBallTextGenerator()
{
  for(size_t hist_id=0; hist_id<histograms.size(); hist_id++)
     delete histograms[hist_id];

  for(size_t tuple_id=0; tuple_id<tuples.size(); tuple_id++)
     delete tuples[tuple_id];

  histograms.erase(histograms.begin(), histograms.end());
  tuples.erase(tuples.begin(), tuples.end());
}

MiniBallHistogram* MiniBallTextGenerator::NewHistogram1D(G4String histo_name,
		             G4int bin, G4double low, G4double high)
{
  MiniBallTextHistogram* new_hist
    = new MiniBallTextHistogram(histo_name, bin, low, high);

  histograms.push_back(new_hist);

  return(new_hist);
}

MiniBallTuple* MiniBallTextGenerator::NewTuple(G4String tuple_name)
{
  MiniBallTextTuple* new_tuple = new MiniBallTextTuple(tuple_name);

  tuples.push_back(new_tuple);

  return(new_tuple);
}

void MiniBallTextGenerator::Close()
{
  for(size_t hist_id=0; hist_id<histograms.size(); hist_id++)
     histograms[hist_id]->Close();
  
  for(size_t tuple_id=0; tuple_id<tuples.size(); tuple_id++)
    tuples[tuple_id]->Close();
}

