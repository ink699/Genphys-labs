Int_t collect_data(Double_t** f1, Double_t** u1, Double_t** phi1, Double_t** f1n, Double_t** u1n, Double_t** f1er, Double_t** u1er, Double_t** phi1er, Double_t** f1ner, Double_t** u1ner, Double_t** f2, Double_t** u2, Double_t** phi2, Double_t** f2n, Double_t** u2n, Double_t** f2er, Double_t** u2er, Double_t** phi2er, Double_t** f2ner, Double_t** u2ner)
{
  string s;
  stringstream ss;
  ifstream in("Dat_plt.txt");
  Double_t tc = 0;
  Double_t** dat = new Double_t* [20];
  for(int i = 0; i < 20; ++i)
  {
    dat[i] = new Double_t;
  }
  Int_t j = 0;
  for(int i = 0; i < 20; ++i)
  {
    getline(in, s);
    ss << s;
    j = 0;
    while(ss >> tc)
    {
      dat[i] = (Double_t*)realloc(dat[i], (j+1)*sizeof(Double_t));
      (*(dat + i))[j] = tc;
      ++j;
    }
    ss.clear();
  }
  *f1 = dat[0];
  *u1 = dat[1];
  *phi1 = dat[2];
  *f1n = dat[3];
  *f1er = dat[4];
  *u1er = dat[5];
  *phi1er = dat[6];
  *f1ner = dat[7];
  *u1n = dat[8];
  *u1ner = dat[9];
  *f2 = dat[10];
  *u2 = dat[11];
  *phi2 = dat[12];
  *f2n = dat[13];
  *f2er = dat[14];
  *u2er = dat[15];
  *phi2er = dat[16];
  *f2ner = dat[17];
  *u2n = dat[18];
  *u2ner = dat[19];
  return j;
}

void draw_gr_afc(Int_t num, Double_t* f1, Double_t* u1, Double_t* f1er, Double_t* u1er, Double_t* f2, Double_t* u2, Double_t* f2er, Double_t* u2er) //ненормированная АЧХ
{
  TCanvas *MyC = new TCanvas("MyC","",1000, 1000);
  MyC->SetGrid();
  TH1F *hr = MyC->DrawFrame(19, 0.0, 35, 2.7);
  hr->SetXTitle("f, kHz");
  hr->SetYTitle("U_{C}, V");
  TGraph *gr1 = new TGraphErrors(num,f1,u1,f1er,u1er);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  TGraph *gr2 = new TGraphErrors(num,f2,u2,f2er,u2er);
  gr2->SetLineColor(2);
  gr2->SetLineWidth(1);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  TMultiGraph  *mg  = new TMultiGraph();

  TF1* fit_func1 = new TF1("fit_func1", "0.1000*sqrt((([0]*2.0*3.141592*x*0.000025)^2+1)/((x/([1]*[2]))^2+((x/[1])^2-1.0)^2))", 19, 35);
  TF1* fit_func2 = new TF1("fit_func2", "0.1000*sqrt((([0]*2.0*3.141592*x*0.0000475)^2+1)/((x/([1]*[2]))^2+((x/[1])^2-1.0)^2))", 19, 35);
  fit_func1->SetParameters(0, 31, 10);
  fit_func1->SetLineColor(4);
  fit_func2->SetParameters(0, 21, 10);
  fit_func2->SetLineColor(2);

  gr1->Fit("fit_func1", "R");
  gr2->Fit("fit_func2", "R");
  cout << fit_func1->GetMaximum(0, 35) << endl;;
  cout << fit_func2->GetMaximum(0, 35) << endl;

  TLegend* lg = new TLegend(0.83, 0.55, 1., 0.45);
  lg->AddEntry(gr1, "C = 25 nF", "PLE");
  lg->AddEntry(gr2, "C = 47.5 nf", "PLE");

  mg->Add(gr1);
  mg->Add(gr2);
  mg->Draw("P");
  lg->Draw();
}

void draw_gr_pfc(Int_t num, Double_t* f1n, Double_t* phi1, Double_t* f1ner, Double_t* phi1er, Double_t* f2n, Double_t* phi2, Double_t* f2ner, Double_t* phi2er)//нормированная ФЧХ
{
  TCanvas *MyC1 = new TCanvas("MyC1","",1000, 1000);
  MyC1->SetGrid();
  TH1F *hr = MyC1->DrawFrame(0.9, 0.3, 1.2, 3.0);
  hr->SetXTitle("f/f_{0}");
  hr->SetYTitle("#varphi");
  TGraph *gr1 = new TGraphErrors(num,f1n,phi1,f1ner,phi1er);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  TGraph *gr2 = new TGraphErrors(num,f2n,phi2,f2ner,phi2er);
  gr2->SetLineColor(2);
  gr2->SetLineWidth(1);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  TMultiGraph  *mg  = new TMultiGraph();

  TF1* fit_func1 = new TF1("fit_func1", "TMath::ACos((x*[0]*(x*2*TMath::Pi()*31.48)*0.000025/[1] - (x^2 - 1))/(TMath::Sqrt([0]^2*(x*2*TMath::Pi()*31.48)^2+1)*TMath::Sqrt(x^2/[1]^2+(x^2-1)^2)))", 0.9, 1.2);
  TF1* fit_func2 = new TF1("fit_func2", "TMath::ACos((x*[0]*(x*2*TMath::Pi()*23.10)*0.0000475/[1] - (x^2 - 1))/(TMath::Sqrt([0]^2*(x*2*TMath::Pi()*23.10)^2+1)*TMath::Sqrt(x^2/[1]^2+(x^2-1)^2)))", 0.9, 1.2);
  fit_func1->SetParameters(0,26);
  fit_func1->SetLineColor(4);
  fit_func2->SetParameters(0,20);
  fit_func2->SetLineColor(2);

  gr1->Fit("fit_func1", "R");
  gr2->Fit("fit_func2", "R");

  TLegend* lg = new TLegend(0.83, 0.55, 1., 0.45);
  lg->AddEntry(gr1, "C = 25 nF", "PLE");
  lg->AddEntry(gr2, "C = 47.5 nf", "PLE");

  mg->Add(gr1);
  mg->Add(gr2);
  mg->Draw("P");
  lg->Draw();
}

void draw_gr_afc_n(Int_t num, Double_t* f1n, Double_t* u1n, Double_t* f1ner, Double_t* u1ner, Double_t* f2n, Double_t* u2n, Double_t* f2ner, Double_t* u2ner)//нормированная АЧХ
{
  TCanvas *MyC2 = new TCanvas("MyC2","",1000, 1000);
  MyC2->SetGrid();
  TH1F *hr = MyC2->DrawFrame(0.78, 0.0, 1.2, 1.0);
  hr->SetXTitle("f/f_{0}");
  hr->SetYTitle("U_{C}/U_{0}, V");
  TGraph *gr1 = new TGraphErrors(num,f1n,u1n,f1ner,u1ner);
  gr1->SetLineColor(4);
  gr1->SetLineWidth(1);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
  TGraph *gr2 = new TGraphErrors(num,f2n,u2n,f2ner,u2ner);
  gr2->SetLineColor(2);
  gr2->SetLineWidth(1);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  TMultiGraph  *mg  = new TMultiGraph();


  TF1* fit_func1 = new TF1("fit_func1", "sqrt((([0]*2.0*3.141592*x*0.000025*31.48)^2+1)/(x^2/[1]^2+((x)^2-1.0)^2))/[1]", 0.78, 1.2);
  TF1* fit_func2 = new TF1("fit_func2", "sqrt((([0]*2.0*3.141592*x*0.0000475*23.10)^2+1)/((x/[1])^2+((x)^2-1.0)^2))/[1]", 0.78, 1.2);
  fit_func1->SetParameters(0, 26);
  fit_func1->SetLineColor(4);
  fit_func2->SetParameters(0, 20);
  fit_func2->SetLineColor(2);

  gr1->Fit("fit_func1", "R");
  gr2->Fit("fit_func2", "R");

  TLegend* lg = new TLegend(0.83, 0.55, 1., 0.45);
  lg->AddEntry(gr1, "C = 25 nF", "PLE");
  lg->AddEntry(gr2, "C = 47.5 nf", "PLE");

  mg->Add(gr1);
  mg->Add(gr2);
  lg->Draw();
  mg->Draw("P");
}

void do_everything() //делает все от слова совсем
{
  Double_t* f1;
  Double_t* u1;
  Double_t* phi1;
  Double_t* f1n;
  Double_t* u1n;
  Double_t* f1er;
  Double_t* u1er;
  Double_t* phi1er;
  Double_t* f1ner;
  Double_t* u1ner;
  Double_t* f2;
  Double_t* u2;
  Double_t* phi2;
  Double_t* f2n;
  Double_t* u2n;
  Double_t* f2er;
  Double_t* u2er;
  Double_t* phi2er;
  Double_t* f2ner;
  Double_t* u2ner;
  Int_t num = collect_data (&f1,  &u1, &phi1, &f1n, &u1n, &f1er, &u1er, &phi1er, &f1ner, &u1ner, &f2, &u2, &phi2, &f2n, &u2n, &f2er, &u2er, &phi2er, &f2ner, &u2ner);
  draw_gr_afc(num, f1, u1, f1er, u1er, f2, u2, f2er, u2er);
  draw_gr_pfc(num, f1n, phi1, f1ner, phi1er, f2n, phi2, f2ner, phi2er);
  draw_gr_afc_n(num, f1n, u1n, f1ner, u1ner, f2n, u2n, f2ner, u2ner);
}
