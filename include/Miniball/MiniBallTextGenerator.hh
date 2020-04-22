///////////////////////////////////////////////////////////////////////////////
/**  \file
 *   \brief  handle histogramming using simple ascii files
 **/ 
//////////////////////////////////////////////////////////////////////////////

#ifndef MiniBallTextGenerator_h
#define MiniBallTextGenerator_h 1

#include "MiniBallHistoGenerator.hh"

#include <fstream>
#include <vector>

#define HIST_FILE_EXT ".hist.dat"

/// Text histogramm. Could be view e.g. in gnuplot 
class MiniBallTextHistogram : public MiniBallHistogram
{
public:
  MiniBallTextHistogram(G4String hist_name, G4int bin,
			G4double low, G4double high);
  ~MiniBallTextHistogram();
  
public:
  /// increments an histogramm at a given value.
  void Fill(G4double value);

  /// sets content of a given bin 
  /// bin numbers may range from 0 to nb_of_bins-1
  void SetBinContent(G4int bin, G4double content);

  /// sets content of a given bin 
  /// bin numbers may range from 0 to nb_of_bins-1
  G4double GetBinContent(G4int bin);

  /// closes the file
    void Close();

  private:
    G4int* data;

    G4int bin;
    G4double low, eff_low;
    G4double high, eff_high;
    G4double bin_size;

    G4int overflow;
    G4int underflow;

    G4bool file_written; 

	 std::ofstream hist_file;
};

#define TUPLE_FILE_EXT ".tup.dat"

/// Virtual class for an ntuple. Replace e.g. by an root-tree.
class MiniBallTextTuple : public MiniBallTuple
{
  public:
    MiniBallTextTuple(G4String tuple_name);
   ~MiniBallTextTuple();

  public:
  /// Adds new column to ntuple with name field_name.
  /** Returns the identifier with which the column must be referred to.*/
    G4int AddColumn(G4String field_name, G4double default_value=0);

  /// Fills a given value into a column of a ntuple.
  /** The column must be referred to using the column identifier.*/
    void FillColumn(G4int column_id, G4double value);

  /// Fills all values into the ntuple.
    void Fill();

  /// Clears all values, do not fill them.
    void Clear();
  /// Closes the tuple
    void Close();

  private:
	 std::vector<G4double> column_values;
	 std::vector<G4double> column_default;

	 std::ofstream tuple_file;

    G4bool started_writing;
};

/// Organization of a simple Ascii-File 
class MiniBallTextGenerator : public MiniBallHistoGenerator 
{
  public:
    MiniBallTextGenerator();
   ~MiniBallTextGenerator();

  public:
  /// Generate a new 1-dim histogram
    MiniBallHistogram* NewHistogram1D(G4String histo_name,
		                      G4int bin, G4double low, G4double high);

  /// Generate a new ntuple
    MiniBallTuple* NewTuple(G4String tuple_name);

  /// Close file
    void Close();

  private:
	 std::vector<MiniBallTextHistogram*> histograms;
	 std::vector<MiniBallTextTuple*> tuples;
};
#endif
