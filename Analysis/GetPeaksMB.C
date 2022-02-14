
#include <TROOT.h>

#include <stdio.h>
#include "th22mama_hist.C"

////////////////////////////
// Parameters
// double threshold = 300.; // Detector threshold in MeV
double threshold = 0.; // Detector threshold in MeV
double smoothingFactor = 100.; // smoothing for the mama output 
////////////////////////////

std::vector<double> GetEnergies(){
    std::vector<double> energies;
    energies.push_back(50);
    energies.push_back(100);
    for ( int en = 200 ; en <= 10000 ; en += 200 ){
        energies.push_back(en);
    }
    return energies;
}

std::string GetFname(int energy)
{
    char fname[16384];
    sprintf(fname, "/Volumes/RootTrees/result/Eg_%d/Eg%d.root", energy, energy);
    return fname;
}

TH1* GetHist(TTree *tree, int energy)
{
    char tmp[1024];
    sprintf(tmp, "h_%dkeV", energy);
    TH1 *h = new TH1F(tmp, tmp, 21000, 0, 21);

    sprintf(tmp, "Miniball.fCrystal.fCoreEnergy*0.001>>h_%dkeV", energy);

    tree->Draw(tmp, "Miniball.fClusterID < 6 & Miniball.fCrystal.fCoreEnergy > 0");
    return h;
}


TH1* ScaleX(TH1* h, double scaleFactor){
  // Scale histogram X axis 
  // double ScaleX = 1.e3; //

    int nBinsx = h->GetXaxis()->GetNbins();
    double xmin = h->GetXaxis()->GetXmin();
    double xmax = h->GetXaxis()->GetXmax();
    //cout << "h before scaling"<< endl;;
    //cout << "xmin: " << xmin << "; xmax:" << xmax << endl;
    xmax *= scaleFactor;
    h->GetXaxis()->Set(nBinsx,xmin,xmax);
    //cout << "h after scaling" << endl;;
    //cout << "xmin: " << xmin << "; xmax:" << xmax << endl;
    return h;
}

double GetBinFromXval(TH1* h1, double xValueofBin)
{
  TAxis *xaxis = h1->GetXaxis();
  TAxis *yaxis = h1->GetYaxis();
  Int_t binx = xaxis->FindBin(xValueofBin);
  double binvalue = h1->GetBinContent(binx);
  return binvalue;
}

double GetBinWoBG(TH1* h1,double xValueofBin ,Int_t nChannelsBG)
{
  TAxis *xaxis = h1->GetXaxis();
  TAxis *yaxis = h1->GetYaxis();
  Int_t binx = xaxis->FindBin(xValueofBin);
  double binvalue = h1->GetBinContent(binx);


  double cntsInPeak = binvalue;
  cntsInPeak += h1->GetBinContent(binx+1) + h1->GetBinContent(binx-1);

  // get BG
  Int_t min = binx-nChannelsBG;
  Int_t max = binx + nChannelsBG;
  cout << "Subtract BG from " <<  h1->GetXaxis()->GetBinCenter(min)
       << "to " <<  h1->GetXaxis()->GetBinCenter(max) << endl;
  double sum = 0;
  for(int ch=min;ch<max+1;ch++ ){
    sum += h1->GetBinContent(ch);
  }
  // a little messy -- this accounts also for thaat counts can come in the bin below/above
  int nchTot = 2*nChannelsBG +1;
  int nchBGonly = nchTot -3;
  double cntbg = (sum - cntsInPeak) / nchBGonly; // bg per channel
  double cntWobg = cntsInPeak - cntbg*3.;
  return cntWobg;

}

TH1D* CreateMamaSpectrum(TH1* h, double EgFE, int nChannelsBG=3)
{
  TH1D* h1 = (TH1D*) h->Clone(); // create output spectrum as a clone
  h1->SetTitle("hmama");
  h1->SetName("hmama");

  vector<double> peaks;
  if(EgFE>=1022.)
  {
  peaks.insert(peaks.end(), {EgFE, EgFE-511., EgFE-2.*511., 511.});
  }
  else
  {
  peaks.insert(peaks.end(), {EgFE});
  }

  TAxis *xaxis = h1->GetXaxis();
  TAxis *yaxis = h1->GetYaxis();


  for(auto Eg : peaks)
  {
    Int_t  binx     = xaxis->FindBin(Eg);
    double binvalue = h1->GetBinContent(binx);

    double cntsInPeak = binvalue;
    cntsInPeak += h1->GetBinContent(binx+1) + h1->GetBinContent(binx-1);

    // get BG
    Int_t min = binx - nChannelsBG;
    Int_t max = binx + nChannelsBG;
    // cout << "Subtract BG from " <<  h1->GetXaxis()->GetBinCenter(min)
    // << "to " <<  h1->GetXaxis()->GetBinCenter(max) << endl;
    double sum = 0;
    for(int ch=min;ch<max+1;ch++ ){
      sum += h1->GetBinContent(ch);
    }
    // a little messy -- this accounts also for thaat counts can come in the bin below/above
    int nchTot = 2*nChannelsBG +1;
    int nchBGonly = nchTot -3;
    double cntbg = (sum - cntsInPeak) / nchBGonly; // bg per channel

    // set all counts equal to bg
    for(int ch=min;ch<max+1;ch++ ){
      h1->SetBinContent(ch,cntbg);
    }
  }

  return h1;
}

void GetPeaksMB()
{

    auto energies = GetEnergies();
    TCanvas *mycan = new TCanvas();

    vector<double> Eg;
    vector<double> nEvents;
    vector<double> nCounts;
    vector<double> cntFE ;
    vector<double> cntSE ;
    vector<double> cntDE ;
    vector<double> cnt511;
    vector<double> cntRest;
    vector<double> cntRestNoThres;
    Int_t nChannelsBG = 3;// # of channels, symmetric, to choose to average out the BG around the peaks
    int xstart; // dummy for startbin
    int xstop; // dummy for stop bin
    double sum; // dummy for a sum

    double EgFE;

    TH1D* hmama; // output spectrum for mama
    TH1D* hmama_raw; // before smoothing



    string fout_name = "Peaks_mb.dat";
    system("xterm -e 'mkdir mama_spectra_mb'"); // create dir for mama spectra, if not already existend
    string outdir = "mama_spectra_mb";


    for ( auto &energy : energies ){
        
        auto *file_root = TFile::Open(GetFname(energy).c_str());
        TTree *tree;
        file_root->GetObject("treeDet",tree);
        std::cout << "Processing energy: " << energy << " keV" << std::endl;
        TH1 *hist = GetHist(tree, energy);

        hist = ScaleX(hist, 1e3);
        hist->Draw();
        mycan->Print("mbhis.gif+");

        EgFE = energy;
        Eg.push_back(energy);
        cntFE.push_back(GetBinWoBG(hist,EgFE,nChannelsBG));

        //nChannelsBG = 3;
        if ( EgFE < 1022. ){
            cntSE.push_back(0);
            cntDE.push_back(0);
            cnt511.push_back(0);
        } else {
            cntSE.push_back(GetBinWoBG(hist,EgFE-511.,nChannelsBG));
            cntDE.push_back(GetBinWoBG(hist,EgFE-2.*511.,nChannelsBG));
            cnt511.push_back(GetBinWoBG(hist,511.,nChannelsBG));
        }
        nCounts.push_back(hist->GetEntries());

        xstart = hist->GetXaxis()->FindBin(threshold);
        sum = 0;
        for(int i=xstart; i < hist->GetXaxis()->GetNbins() ; i++){
            sum += hist->GetBinContent(i);
        }
        cntRest.push_back(sum - ( cntFE.back() + cntSE.back() + cntDE.back() + cnt511.back()));

        nEvents.push_back(10000000);


        hmama = CreateMamaSpectrum(hist, EgFE, nChannelsBG);
        hmama->Smooth(smoothingFactor);
        hmama->Draw();

        cntRestNoThres.push_back(hmama->GetEffectiveEntries());
        string Egpp = to_string(int(EgFE));

        auto fname_mamaStr = outdir + "/" + "cmp" + Egpp;
        const char *fname_mama = fname_mamaStr.c_str();
        th22mama_hist(hmama, fname_mama);

        std::cout <<"# Eg[keV]" << "\t" 
                  << "nEvents" << "\t" 
                  << "nCounts" << "\t"  
                  << "cntFE" << "\t"
                  << "cntSE" << "\t"
                  << "cntDE" << "\t"
                  << "cnt511" << "\t"
                  << "cntRest" << "\t"
                  << "cntRestNoThres" << std::endl;
        std::cout << Eg.back() << "\t\t";
        std::cout << nEvents.back() << "\t";
        std::cout << nCounts.back() << "\t";
        std::cout << cntFE.back() << "\t";
        std::cout << cntSE.back() << "\t";
        std::cout << cntDE.back() << "\t";
        std::cout << cnt511.back() << "\t";
        std::cout << cntRest.back() << "\t";
        std::cout << cntRestNoThres.back() << std::endl;

    }

    // Write vectors to file
    std::ofstream fout(fout_name);
    fout << "# Eg[keV]" << "\t" 
    << "nEvents" << "\t" 
    << "nCounts" << "\t"  
    << "cntFE" << "\t"
    << "cntSE" << "\t"
    << "cntDE" << "\t"
    << "cnt511" << "\t"
    << "cntRest" << "\t" <<
    "cntRestNoThres" << endl;
    for(vector<double>::size_type i = 0; i != cntFE.size(); i++) {
        fout 
        << Eg[i] << "\t"
        << nEvents[i] << "\t" 
        << nCounts[i] << "\t" 
        << cntFE[i] << "\t" 
        << cntSE[i] << "\t" 
        << cntDE[i] << "\t" 
        << cnt511[i] << "\t" 
        << cntRest[i] << "\t" 
        << cntRestNoThres[i] << endl;
    }
    fout.close();

}