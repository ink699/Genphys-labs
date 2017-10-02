void do_everything2()
{
  Double_t sqf[7], sqfer[7], r[7], rer[7], f[7], fer[7];
  ifstream in("Dat_plt_2.txt");
  for(Int_t i = 0; i < 7; ++i)
    in >> sqf[i];
  for(Int_t i = 0; i < 7; ++i)
    in >> sqfer[i];
  for(Int_t i = 0; i < 7; ++i)
    in >> r[i];
  for(Int_t i = 0; i < 7; ++i)
    in >> rer[i];
  for(Int_t i = 0; i < 7; ++i)
    in >> f[i];
  for(Int_t i = 0; i < 7; ++i)
    in >> fer[i];
  TCanvas *MyC4 = new TCanvas("MyC4","",1000, 1000);
  MyC4->SetGrid();
  TH1F *hr = MyC4->DrawFrame(15, 3.3, 32, 4.4);
  hr->SetXTitle("f, kHz");
  hr->SetYTitle("R_{L}, #Omega");
  TGraph *gr1 = new TGraphErrors(7,f,r,fer,rer);
  gr1->SetLineColor(1);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(1);
  gr1->SetMarkerStyle(20);

  Double_t chi1;
  Double_t chi2;
  TF1* fit_func1 = new TF1("fit_func1", "[1]*sqrt(x) + [0]", 15, 32);
  TF1* fit_func2 = new TF1("fit_func2", "[0] + [1] * sqrt(x) + [2]*x + [3]*x^2", 15 ,32);
  TLegend* lg = new TLegend(0.85, 0.55, 1., 0.45);
  lg->AddEntry(fit_func2, "mod1", "L");
  lg->AddEntry(fit_func1, "mod2", "L");
  fit_func1->SetLineColor(4);
  fit_func1->SetParameters(1.02566, 0.569698, 0, 0);
  fit_func2->SetLineColor(2);
  gr1->Fit("fit_func1");
  gr1->Fit("fit_func2", "R+");
  chi1 = fit_func1->GetChisquare();
  chi2 = fit_func2->GetChisquare();
  cout << chi1 << " " << chi2 << endl;

  gr1->Draw("P");
  lg->Draw();
}
