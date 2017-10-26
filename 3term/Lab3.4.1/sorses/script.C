void dr_gr_cal(Double_t* I, Double_t* B, Double_t* Ierr, Double_t* Berr)
{
  TCanvas *MyC = new TCanvas("MyC","",1000, 1000);
  MyC->SetGrid();
  TH1F *hr = MyC->DrawFrame(0.0, 0.0, 3.2, 1.0);
  hr->SetXTitle("I, A");
  hr->SetYTitle("B, Tl");
  TGraph *gr1 = new TGraphErrors(8,I,B,Ierr,Berr);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);

  TF1* fit_func1 = new TF1("fit_func1", "[0]*x + [1]*x^2", 0, 3.2);
  fit_func1->SetLineColor(4);
  gr1->Fit("fit_func1", "R");

  gr1->Draw("P");
}

void dr_gr_B(Double_t* modPAl, Double_t* modPCu, Double_t* modPGr, Double_t* modPerr, Double_t* B2, Double_t* B2err)
{
  TCanvas *MyC1 = new TCanvas("MyC1","",1000, 1000);
  MyC1->SetGrid();
  TH1F *hr = MyC1->DrawFrame(0.0, 0.0, 0.8, 1.5);
  hr->SetXTitle("B^{2}, Tl^{2}");
  hr->SetYTitle("|P|, mN");
  TGraph *gr1 = new TGraphErrors(8,B2,modPAl,B2err,modPerr);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  TGraph *gr2 = new TGraphErrors(8,B2,modPCu,B2err,modPerr);
  gr2->SetLineColor(2);
  gr2->SetLineWidth(1);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  TGraph *gr3 = new TGraphErrors(8,B2,modPGr,B2err,modPerr);
  gr3->SetLineColor(6);
  gr3->SetLineWidth(1);
  gr3->SetMarkerColor(6);
  gr3->SetMarkerStyle(20);
  TMultiGraph  *mg  = new TMultiGraph();

  TF1* fit_func1 = new TF1("fit_func1", "[0]*x", 0.0, 0.8);
  TF1* fit_func2 = new TF1("fit_func2", "[0]*x", 0.0, 0.8);
  TF1* fit_func3 = new TF1("fit_func3", "[0]*x", 0.0, 0.8);
  fit_func1->SetLineColor(4);
  fit_func2->SetLineColor(2);
  fit_func3->SetLineColor(6);

  gr1->Fit("fit_func1", "R");
  gr2->Fit("fit_func2", "R");
  gr3->Fit("fit_func3", "R");

  TLegend* lg = new TLegend(0.83, 0.55, 1., 0.45);
  lg->AddEntry(gr1, "Aluminium", "PLE");
  lg->AddEntry(gr2, "Copper", "PLE");
  lg->AddEntry(gr3, "Graphite", "PLE");

  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Draw("P");
  lg->Draw();
}

void do_everything()
{
  ifstream in("Dat.txt");
  Double_t I[8];
  Double_t B[8];
  Double_t Ierr[8];
  Double_t Berr[8];
  Double_t modPAl[8];
  Double_t modPCu[8];
  Double_t modPGr[8];
  Double_t modPerr[8];
  Double_t B2[8];
  Double_t B2err[8];
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> I[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> B[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> Ierr[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> Berr[i];
  }

  dr_gr_cal(I,B,Ierr,Berr);

  for(Int_t i = 0; i < 8; ++i)
  {
    in >> modPAl[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> modPCu[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> modPGr[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> modPerr[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> B2[i];
  }
  for(Int_t i = 0; i < 8; ++i)
  {
    in >> B2err[i];
  }

  dr_gr_B(modPAl, modPCu, modPGr, modPerr, B2, B2err);
}
