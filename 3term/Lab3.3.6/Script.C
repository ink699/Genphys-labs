void dr_gr_cal(Double_t** args)
{
  TCanvas *MyC = new TCanvas("MyC","",1000, 1000);
  MyC->SetGrid();
  TH1F *hr = MyC->DrawFrame(0.0, 0.0, 0.5, 400);
  hr->SetXTitle("I, A");
  hr->SetYTitle("B, mTl");
  TGraph *gr1 = new TGraphErrors(8,args[0],args[1],args[2],args[3]);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);

  TF1* fit_func1 = new TF1("fit_func1", "[0]*x + [1] * x^2", 0, 0.25);
  fit_func1->SetParameters(0, 0);
  fit_func1->SetLineColor(4);
  gr1->Fit("fit_func1", "R");

  gr1->Draw("P");
}

void dr_gr_R(Double_t** args)
{
  TCanvas *MyC1 = new TCanvas("MyC1","",1000, 1000);
  MyC1->SetGrid();
  TH1F *hr = MyC1->DrawFrame(0.0, 0.0, 140, 400);
  hr->SetXTitle("B^{2}, mTl^{2}/10^{3}");
  hr->SetYTitle("R, m#Omega");

  TGraph *gr1 = new TGraphErrors(8,args[4],args[6],args[5],args[7]);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  TGraph *gr2 = new TGraphErrors(8,args[4],args[8],args[5],args[9]);
  gr2->SetLineColor(2);
  gr2->SetLineWidth(1);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  TGraph *gr3 = new TGraphErrors(8,args[4],args[10],args[5],args[11]);
  gr3->SetLineColor(6);
  gr3->SetLineWidth(1);
  gr3->SetMarkerColor(6);
  gr3->SetMarkerStyle(20);
  TMultiGraph  *mg  = new TMultiGraph();

  TF1* fit_func1 = new TF1("fit_func1", "[0]*x + [1]", 0.0, 140);
  TF1* fit_func2 = new TF1("fit_func2", "[0]*x + [1]", 0.0, 140);
  TF1* fit_func3 = new TF1("fit_func3", "[0]*x + [1]", 0.0, 140);
  fit_func1->SetLineColor(4);
  fit_func2->SetLineColor(2);
  fit_func3->SetLineColor(6);

  gr1->Fit("fit_func1", "R");
  gr2->Fit("fit_func2", "R");
  gr3->Fit("fit_func3", "R");

  TLegend* lg = new TLegend(0.83, 0.55, 1., 0.45);
  lg->AddEntry(gr1, "Korbino", "PLE");
  lg->AddEntry(gr2, "Plate, parallel", "PLE");
  lg->AddEntry(gr3, "Plate, normal", "PLE");

  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Draw("P");
  lg->Draw();
}

void do_everything()
{
  ifstream in("input_dat.txt");
  Double_t** args = new Double_t* [12];
  for(int i = 0; i < 12; ++i)
  {
    args[i] = new Double_t [8];
  }
  for(int i = 0; i < 12; ++i)
  {
    for(int j = 0; j < 8; ++j)
    {
      in >> args[i][j];
    }
  }
  dr_gr_cal(args);
  dr_gr_R(args);
}
