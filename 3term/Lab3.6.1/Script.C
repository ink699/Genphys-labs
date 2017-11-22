void dr_sp_m()
{
  Double_t ampl1[19] = {2.82,2.71,2.65,2.53,2.4,2.24,2.07,1.9,1.73,1.58,1.49,1.33,1.18,1,0.82,0.64,0.44,0.28};
  Double_t freq[19] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  Double_t ampl2[16] = {5.55,5.19,4.69,4.08,3.37,2.62,1.87,1.18,0.53,0,0.46,0.82,1.07,1.18,1.16,1.04};
  Double_t ampl_err[19];
  Double_t freq_err[19];

  TF1* th = new TF1("th", "abs([0]*sin([1]*x)/([1]*x))", 0, 20);
  th->SetParameters(0.1, 3.1415926*0.05);
  th->FixParameter(0,0.1);
  th->FixParameter(1,3.1415926*0.05);

  TCanvas *MyC = new TCanvas("MyC","6",1000, 500);
  MyC->SetGrid();
  MyC->Divide(2);
  MyC->cd(1)->SetGrid();


  TH1F *hr = MyC->DrawFrame(0.0, 0.0, 20.0, 0.1);
  hr->SetXTitle("f, kHz");
  hr->SetYTitle("A, V");

  for(Int_t i = 0; i < 19; ++i)
  {
    ampl1[i]*=(0.0365);
    ampl_err[i] = 0.0002;
    freq_err[i] = 0;
  }

  TGraph *gr1 = new TGraphErrors(18,freq,ampl1,freq_err,ampl_err);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);

  gr1->Fit(th, "R");
  gr1->Draw("P");

  th->SetParameters(0.1, 3.1415926*0.05);
  th->FixParameter(0,0.2);
  th->FixParameter(1,3.1415926*0.1);

  MyC->cd(2)->SetGrid();

  TH1F *hr1 = MyC->DrawFrame(0.0, 0.0, 20.0, 0.2);
  hr1->SetXTitle("f, kHz");
  hr1->SetYTitle("A, V");

  for(Int_t i = 0; i < 16; ++i)
  {
    ampl2[i]*=(0.0365);
    ampl_err[i] = 0.0002;
    freq_err[i] = 0;
  }

  TGraph *gr2 = new TGraphErrors(16,freq,ampl2,freq_err,ampl_err);
  gr2->SetLineColor(4);
  gr2->SetLineWidth(1);
  gr2->SetMarkerColor(4);
  gr2->SetMarkerStyle(20);

  gr2->Fit(th, "R");
  gr2->Draw("P");
}

void dr_sp_gr()
{
  Double_t nu[9] = {24.2,16.2,12.0,9.9,8.4,7.1,6.3,5.5,5.0};
  Double_t ft[9] = {25.0,16.7,12.5,10.0,8.3,7.1,6.3,5.6,5.0};
  Double_t nu_err[9] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
  Double_t ft_err[9] = {0};
  TF1* ff = new TF1("ff", "[0]*x", 4, 25);
  ff->SetParameters(1, 0);

  TCanvas *MyC1 = new TCanvas("MyC1","7",1000, 1000);
  MyC1->SetGrid();

  TH1F *hr = MyC1->DrawFrame(5.0, 5.0, 25.0, 25);
  hr->SetXTitle("#Delta#nu, kHz");
  hr->SetYTitle("1/#tau, kHz");

  TGraph *gr1 = new TGraphErrors(9,nu,ft,nu_err,ft_err);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  gr1->Fit(ff, "R");
  gr1->Draw("P");
}

void dr_gr_cug()
{
  Double_t ampl1[21] = {19.32,19.32,17.32,13.55,7.33,0,8.44,17.77,27.09,36.2,43.75,50.19,54.85,59.46,63.74,69.73,64.4,60.45,55.52,48.64,40.64};
  Double_t freq1[21] = {15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
  Double_t freq2[21] = {15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
  Double_t ampl2[21] = {0,7.21,27.48,27.07,16.38,0,18.74,34.42,38.45,26.93,0,36.23,72.73,100.8,120.7,134.9,121.6,97.16,63.15,28.18,0};
  Double_t ampl_err[21];
  Double_t freq_err[21];
  for(Int_t i = 0; i < 21; ++i)
  {
    ampl1[i]*=(0.001434);
    ampl2[i]*=(0.0014826);
    ampl_err[i] = 0.0002;
    freq_err[i] = 0;
    freq2[i] = i*2;
  }

  TF1* th1 = new TF1("th1", "abs([0]*(sin([1]-[2]*x)/([1]-[2]*x) + sin([1]+[2]*x)/([1]+[2]*x)))", 0, 40);
  th1->FixParameter(0, 0.1);
  th1->FixParameter(1, 3*3.141592);
  th1->FixParameter(2, 0.1*3.141592);


  TCanvas *MyC2 = new TCanvas("MyC2","8",1000, 500);
  MyC2->SetGrid();
  MyC2->Divide(2);
  MyC2->cd(1)->SetGrid();

  TH1F *hr = MyC2->DrawFrame(0.0, 0.0, 40.0, 0.1);
  hr->SetXTitle("f, kHz");
  hr->SetYTitle("A, V");

  TGraph *gr1 = new TGraphErrors(21,freq1,ampl1,freq_err,ampl_err);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);

  gr1->Fit(th1, "R");
  gr1->Draw("P");

  MyC2->cd(2)->SetGrid();

  th1->FixParameter(0, 0.2);
  th1->FixParameter(1, 3*3.141592);
  th1->FixParameter(2, 0.1*3.141592);

  TH1F *hr1 = MyC2->DrawFrame(0.0, 0.0, 40.0, 0.2);
  hr->SetXTitle("f, kHz");
  hr->SetYTitle("A, V");

  TGraph *gr2 = new TGraphErrors(21,freq2,ampl2,freq_err,ampl_err);
  gr2->SetLineColor(4);
  gr2->SetLineWidth(1);
  gr2->SetMarkerColor(4);
  gr2->SetMarkerStyle(20);

  gr2->Fit(th1);
  gr2->Draw("P");
}
void dr_cug_gr()
{
  Double_t f[5] = {0.5,1,2,4,5};
  Double_t DNu[5] = {0.5,1.01,2,4,5};
  Double_t f_err[5]={0,0,0,0,0};
  Double_t DNu_err[5]={0.01, 0.01, 0.01, 0.01, 0.01};

  TF1* ff1 = new TF1("ff1", "[0]*x", 0, 25);
  ff1->SetParameters(1, 0);

  TCanvas *MyC3 = new TCanvas("MyC3","7",1000, 1000);
  MyC3->SetGrid();

  TH1F *hr = MyC3->DrawFrame(0, 0, 5.0, 5.0);
  hr->SetXTitle("f, kHz");
  hr->SetYTitle("#delta#nu, kHz");

  TGraph *gr1 = new TGraphErrors(5,f,DNu,f_err,DNu_err);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  gr1->Fit(ff1, "R");
  gr1->Draw("P");
}

void dr_gr_mod()
{
  Double_t m[8] = {0.103139013452915,	0.253145445395068,	0.387144992526158,	0.539611360239163,	0.682112605879422,	0.842369477911647,	1};
  Double_t m_err[8] = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02};
  Double_t eq[8] = {0.045454545454546,	0.121212121212121,	0.196969696969697,	0.272727272727273,	0.348484848484848,	0.439393939393939,	0.5};
  Double_t eq_err[8] = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02};

  TF1* ff2 = new TF1("ff2", "[0]*x", 0, 25);
  ff2->SetParameters(1, 0);

  TCanvas *MyC4 = new TCanvas("MyC3","7",1000, 1000);
  MyC4->SetGrid();

  TH1F *hr = MyC4->DrawFrame(0, 0, 1, 0.5);
  hr->SetXTitle("m");
  hr->SetYTitle("A_{s}/A_{m}");

  TGraph *gr1 = new TGraphErrors(7,m,eq,m_err,eq_err);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  gr1->Fit(ff2, "R");
  gr1->Draw("P");
}
void do_everything()
{
  //dr_sp_m();
  //dr_sp_gr();
  //dr_gr_cug();
  //dr_cug_gr();
  dr_gr_mod();
}
