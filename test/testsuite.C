// macro for reading back and putting in form the histograms created by TestSuite.cc
{
TFile f("histos.root");
int bcr, bcrstart=-5,bcrend=3;

char name[50] ;
TH1I * hist;

// SimTracks
sprintf(name,"SimTracks",bcr);
TCanvas *c = new TCanvas(name,name);
gPad->Divide(3,3);
for (bcr=bcrstart;bcr<=bcrend;bcr++)
{
  c->cd(bcr-bcrstart+1);
  sprintf(name,"Tracks_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->Draw();
  sprintf(name,"SignalTracks_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->SetLineColor(kRed);
  hist->Draw("SAME");
}
sprintf(name,"SimTracksVtxPtrs",bcr);
TCanvas *c = new TCanvas(name,name);
gPad->Divide(3,3);
for (bcr=bcrstart;bcr<=bcrend;bcr++)
{
  c->cd(bcr-bcrstart+1);
  sprintf(name,"VtxPointers_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->Draw();
  sprintf(name,"VtxPointers_signal_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->SetLineColor(kRed);
  hist->Draw("SAME");
}

//SimVertices
sprintf(name,"SimVertices",bcr);
TCanvas *c = new TCanvas(name,name);
gPad->Divide(3,3);
for (bcr=bcrstart;bcr<=bcrend;bcr++)
{
  c->cd(bcr-bcrstart+1);
  sprintf(name,"Vertices_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->Draw();
  sprintf(name,"SignalVertices_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->SetLineColor(kRed);
  hist->Draw("SAME");
}

// Tracker
sprintf(name,"Tracker",bcr);
TCanvas *c = new TCanvas(name,name);
gPad->Divide(3,3);
for (bcr=bcrstart;bcr<=bcrend;bcr++)
{
  c->cd(bcr-bcrstart+1);
  sprintf(name,"TrackerHit_Tof_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->Draw();
  sprintf(name,"SignalTrackerHit_Tof_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->SetLineColor(kRed);
  hist->Draw("SAME");
}

//Ecal
sprintf(name,"ECal",bcr);
TCanvas *c = new TCanvas(name,name);
gPad->Divide(3,3);
for (bcr=bcrstart;bcr<=bcrend;bcr++)
{
  c->cd(bcr-bcrstart+1);
  sprintf(name,"EcalEBHit_Tof_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->Draw();
  sprintf(name,"SignalEcalEBHit_Tof_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->SetLineColor(kRed);
  hist->Draw("SAME");
}

//Hcal
sprintf(name,"HCal",bcr);
TCanvas *c = new TCanvas(name,name);
gPad->Divide(3,3);
for (bcr=bcrstart;bcr<=bcrend;bcr++)
{
  c->cd(bcr-bcrstart+1);
  sprintf(name,"HcalHit_Tof_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->Draw();
  sprintf(name,"SignalHcalHit_Tof_bcr_%d",bcr);
  hist = (TH1I*)f.Get(name);
  hist->SetLineColor(kRed);
  hist->Draw("SAME");
}
}
