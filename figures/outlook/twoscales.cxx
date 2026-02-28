/*
//example of macro illustrating how to superimpose two histograms
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"

void twoscales()
{
   //example of macro illustrating how to superimpose two histograms
   //with different scales in the "same" pad.
   // To see the output of this macro, click begin_html <a href="gif/twoscales.gif" >here</a> end_html
   //Author: Rene Brun

   TCanvas *c1 = new TCanvas("c1","hists with different scales",600,400);

   //create/fill draw h1
   gStyle->SetOptStat(kFALSE);
   //TH1F *h1 = new TH1F("h1","my histogram",100,-3,3);
   TPad *  clear_pad = new TPad("clear_pad", "", 0, 0, 1, 1);
   clear_pad->SetFillColor(0);
   clear_pad->SetFillStyle(4000);
   clear_pad->SetFrameFillStyle(0);

   
   TFile *_file0 = TFile::Open("test.root","R");
   TH1F *h1 = dynamic_cast<TH1F*>(_file0->Get("cpfilt_HighEGJet_HLT_HIEle20_WPLoose_Gsf"));
   Int_t i;
   for (i=0;i<h1->GetNbinsX();i++) std::cout<<h1->GetBinContent(i)<<std::endl;

   h1->Draw("");
   c1->SetTicky(0);
   c1->SetLogy(1);
   //c1->Update();

   clear_pad->Draw();
   clear_pad->cd();
   clear_pad->SetTicks(0, 0);
   clear_pad->SetLogy(0);
   gStyle->SetOptStat(kFALSE);
   //c1->cd();
   //create hint1 filled with the bins integral of h1
   TH1F *hint1 = new TH1F("hint1","h1 bins integral",h1->GetNbinsX(),h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
   Float_t sum = 0;
   for (i=1;i<=h1->GetNbinsX();i++) {
      sum += h1->GetBinContent(i);
      hint1->SetBinContent(h1->GetNbinsX()-i,sum/h1->Integral());
      std::cout<<sum/h1->Integral()<<std::endl;
      hint1->SetMarkerStyle(21);
      hint1->SetBinError(h1->GetNbinsX()-i,0);
   }

   //scale hint1 to the pad coordinates
   hint1->GetYaxis()->SetRangeUser(0.4, 1);
   Float_t rightmax = 1.1*hint1->GetMaximum();
   Float_t scale = c1->GetUymax()/rightmax;
   hint1->SetLineColor(kRed);
   std::cout<<scale<<std::endl;
   //hint1->Scale(5);
   hint1->Draw("lp");
   hint1->GetYaxis()->SetLabelSize(0.0000000005);
   hint1->GetYaxis()->SetTickLength(0.0000000005);
   hint1->GetXaxis()->SetLabelSize(0.0000000005);
   hint1->GetXaxis()->SetTickLength(0.0000000005);
    
   //draw an axis on the right side
   TGaxis *axis = new TGaxis(c1->GetUxmax(),c1->GetUymin(),
         c1->GetUxmax(), c1->GetUymax(),0,rightmax,510,"+L");
   axis->SetLineColor(kRed);
   axis->SetLabelColor(kRed);
   axis->Draw();
   clear_pad->Update();
}
*/
     
//example of macro illustrating how to superimpose two histograms
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"

void twoscales()
{
   //example of macro illustrating how to superimpose two histograms
   //with different scales in the "same" pad.
   // To see the output of this macro, click begin_html <a href="gif/twoscales.gif" >here</a> end_html
   //Author: Rene Brun

   TCanvas *c1 = new TCanvas("c1","hists with different scales",600,400);

   //create/fill draw h1
   gStyle->SetOptStat(kFALSE);
   /*
   TH1F *h1 = new TH1F("h1","my histogram",100,-3,3);
   Int_t i;
   for (i=0;i<10000;i++) h1->Fill(gRandom->Gaus(0,1));
   h1->Draw();
   */
   TFile *_file0 = TFile::Open("test.root","R");
   TH1F *h1 = dynamic_cast<TH1F*>(_file0->Get("cpfilt_HighEGJet_HLT_HIEle20_WPLoose_Gsf"));
   Int_t i;
   for (i=0;i<h1->GetNbinsX();i++) {
     std::cout<<h1->GetXaxis()->GetBinLabel(i)<<std::endl;
     TString label;
     label.Append(h1->GetXaxis()->GetBinLabel(i));
     std::cout<<label.Data()<<std::endl;
     TObjArray *tx = label.Tokenize("FilterForHI");
     //tx->Print();
     for (Int_t i = 0; i < tx->GetEntries(); i++) std::cout << ((TObjString *)(tx->At(i)))->String() << std::endl;
     //std::cout<<h1->GetXaxis()->GetBinLabel(i)<<std::endl;
   }
      
   h1->GetYaxis()->SetLabelSize(0.000);
   h1->GetYaxis()->SetTitle("Counts");
   //h1->GetYaxis()->SetTitleSize(0.5);
   h1->Draw();
     
   c1->Update();

   //create hint1 filled with the bins integral of h1
   /*
   TH1F *hint1 = new TH1F("hint1","h1 bins integral",100,-3,3);
   Float_t sum = 0;
   for (i=1;i<=100;i++) {
      sum += h1->GetBinContent(i);
      hint1->SetBinContent(h1->GetNbinsX()-i,sum/h1->Integral());
      hint1->SetMarkerStyle(21);
      hint1->SetBinError(h1->GetNbinsX()-i,0);
   }
   */
   
   TH1F *hint1 = new TH1F("hint1","h1 bins integral",h1->GetNbinsX(),h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
   Float_t sum = 0;
   for (i=1;i<=h1->GetNbinsX();i++) {
      sum += h1->GetBinContent(i);
      hint1->SetBinContent(h1->GetNbinsX()-i+1,sum/h1->Integral());
      std::cout<<h1->GetNbinsX()<< " "<<h1->GetNbinsX()-i<< " "<<sum/h1->Integral()<<std::endl;
      hint1->SetMarkerStyle(21);
      hint1->SetBinError(h1->GetNbinsX()-i+1,0);
      
   }
   
   //scale hint1 to the pad coordinates
   Float_t rightmax = 1.1*hint1->GetMaximum();
   Float_t scale = gPad->GetUymax()/rightmax;
   hint1->SetLineColor(kRed);
   hint1->Scale(scale);
   hint1->Draw("lpsame");
   hint1->GetYaxis()->SetTitle("Efficiency");
   
   //draw an axis on the right side
   TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
         gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
   axis->SetLineColor(kRed);
   axis->SetLabelColor(kRed);
   axis->Draw();
}
