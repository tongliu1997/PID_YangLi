#include "PID_hist.h"
#include "TCanvas.h"
#include "TPad.h"
//par0 is pion, par1 is kaon, par2 is proton
//cent0 is 60-80, cent4 is 0-10
//In PID_hist.h I already reverted the centrality order
//Now index 0 is 0-10%
//ch0 is negative, ch1 is positive
void plot_charge_ratio(const string file_name="5cent_particle_ratios_RuZr_forTong.root"){
    PID_hist hist(file_name);
//    for(int icent=0;icent<5;icent++){
//	hist.spec[0][icent][0]->Draw("same");
//
    TLatex species_label;
    species_label.SetTextAlign(23);
    species_label.SetTextFont(12);
    species_label.SetTextSize(0.1);
    species_label.SetNDC();


    const int cent_tag[6]={0,10,20,40,60,80};
    const string species[2][3]={{"#pi^{-}","K^{-}","#bar{p}"},{"#pi^{+}","K^{+}","p"}};
    gStyle->SetOptStat(0);
  
    TCanvas* c1=new TCanvas("c1","",1400,800);
    TPad* pad[2][3];
    double vert_margin=0.14;
    double hori_margin=0.14;
    for(int icol=0;icol<3;icol++){

	double left_edge=0,right_edge=0.5;
	if(icol==1){left_edge=0.5;right_edge=1;}
	double bottom_edge=0.5,top_edge=1;
	if(icol==2){bottom_edge=0;top_edge=0.5;}
	if(icol==1){bottom_edge=1-0.5/(1-hori_margin);top_edge=1;}


	pad[0][icol]=new TPad(Form("Pad_0_%i",icol),"",left_edge,bottom_edge,right_edge,top_edge);
    }
    pad[0][0]->SetTopMargin(vert_margin);
    pad[0][1]->SetTopMargin(vert_margin*(1-vert_margin));
    pad[0][2]->SetTopMargin(0);
	
    pad[0][0]->SetBottomMargin(0);
    pad[0][1]->SetBottomMargin(vert_margin);
    pad[0][2]->SetBottomMargin(vert_margin);

    pad[0][0]->SetLeftMargin(hori_margin);
    pad[0][1]->SetLeftMargin(0);
    pad[0][2]->SetLeftMargin(hori_margin);

    pad[0][0]->SetRightMargin(0);
    pad[0][1]->SetRightMargin(hori_margin);
    pad[0][2]->SetRightMargin(0);

    pad[0][2]->SetTickx();
    pad[0][0]->SetTicky();


    for(int icol=0;icol<3;icol++){
	c1->cd();
	pad[0][icol]->Draw();
	pad[0][icol]->cd();



	TH1F* dummy=new TH1F(Form("dummy_0_%i",icol),"",1000,0.1,1.999);
	dummy->GetXaxis()->SetRangeUser(0.01,1.999);
	dummy->GetYaxis()->SetRangeUser(0.986,1.014);
	dummy->GetXaxis()->SetNdivisions(505);
	dummy->GetYaxis()->SetNdivisions(505);
	dummy->GetXaxis()->SetLabelSize(0.06);
	if(icol==2){
	    dummy->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	    dummy->GetXaxis()->SetTitleSize(0.06);
	    dummy->GetXaxis()->SetTitleOffset(0.8);
	    dummy->GetYaxis()->SetLabelSize(0.05);
	    dummy->GetYaxis()->SetTitle("dN/dp_{T}");
	    dummy->GetYaxis()->SetTitleSize(.08);
	    dummy->GetYaxis()->SetTitleOffset(0.6);
	}
	if(icol==1){
	    dummy->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	    dummy->GetXaxis()->SetTitleSize(0.06);
	    dummy->GetXaxis()->SetTitleOffset(0.8);

	}

	if(icol==0){
	    dummy->GetYaxis()->SetLabelSize(0.05);
	    dummy->GetYaxis()->SetTitle("Ru+Ru/Zr+Zr ratio");
	    dummy->GetYaxis()->SetTitleSize(.08);
	    dummy->GetYaxis()->SetTitleOffset(0.6);
	}

	dummy->Draw();
 
	TLine* line=new TLine(0.25,1,1.999,1);
 	line->SetLineColor(kMagenta);
	line->SetLineStyle(8);
	line->Draw("same");


	TH1F* plot[5];
	for(int icent=0;icent<5;icent++){
	    plot[icent]=(TH1F*)hist.spec[icol][icent][1]->Clone();//Negative particles
	    plot[icent]->Divide(hist.spec[icol][icent][0]);

	    plot[icent]->SetLineColor(colors[icent]);
	    plot[icent]->SetMarkerColor(colors[icent]);
	    plot[icent]->SetMarkerStyle(markers[icent]);
	    plot[icent]->Draw("same");
	    	
	}
	if(icol==2){
	    TLegend* lg=new TLegend(0.1*(1-hori_margin)+hori_margin,0.03+0.97*vert_margin,0.9+0.1*hori_margin,0.4+0.6*vert_margin);
	    for(int icent=0;icent<5;icent++){
		lg->AddEntry(plot[icent],Form("%i%%-%i%%",cent_tag[icent],cent_tag[icent+1]));
	    }
	    lg->SetBorderSize(0);
	    lg->SetNColumns(2);
	    lg->Draw();
	}

	
	for(int icent=0;icent<5;icent++){
	    plot[icent]->Draw("same");
	}

	double xlabel,ylabel;
	if(icol%2) xlabel=0.7*(1-vert_margin);
	else xlabel=vert_margin+0.7*(1-vert_margin);
	if(icol==0)ylabel=0.9*(1-hori_margin);
	if(icol==1)ylabel=hori_margin+0.9*(1-hori_margin)*(1-hori_margin);
	if(icol==2)ylabel=hori_margin+0.9*(1-hori_margin);
	species_label.DrawLatex(xlabel,ylabel,Form("%s/%s",species[1][icol].c_str(),species[0][icol].c_str()));
    }
    
    TLatex prelim_tag;
    prelim_tag.SetTextAlign(23);
    prelim_tag.SetTextFont(22);
    prelim_tag.SetTextSize(0.07);
    prelim_tag.SetNDC();
    
    pad[0][0]->cd();
    prelim_tag.DrawLatex(0.5,0.45*(1-vert_margin),"STAR #bf{#it{Preliminary}}");
    prelim_tag.DrawLatex(0.5,0.35*(1-vert_margin),"Isobar #sqrt{s_{NN}}=200 GeV");
    prelim_tag.DrawLatex(0.5,0.25*(1-vert_margin),"-0.5<y<0.5");
    prelim_tag.DrawLatex(0.5,0.17*(1-vert_margin),"#bf{statistical uncertainty only}");


    c1->Draw();
    c1->SaveAs("Yang_PID_chg_plot.pdf");
}
