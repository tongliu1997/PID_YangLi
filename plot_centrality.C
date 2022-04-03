#include "PID_hist.h"
#include "TCanvas.h"
#include "TPad.h"
//par0 is pion, par1 is kaon, par2 is proton
//cent0 is 60-80, cent4 is 0-10
//In PID_hist.h I already reverted the centrality order
//Now index 0 is 0-10%
//ch0 is negative, ch1 is positive
void plot_centrality(const string file_name="5cent_particle_ratios_RuZr_forTong.root"){
    PID_hist hist(file_name);
//    for(int icent=0;icent<5;icent++){
//	hist.spec[0][icent][0]->Draw("same");
//
    TLatex species_label;
    species_label.SetTextAlign(23);
    species_label.SetTextFont(22);
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

    pad[0][0]->SetTicky();
    pad[0][2]->SetTickx();


    int cent_select[3]={1,2,3};
    for(int icol=0;icol<3;icol++){
	c1->cd();
	pad[0][icol]->Draw();
	pad[0][icol]->cd();


	TH1F* dummy=new TH1F(Form("dummy_0_%i",icol),"",1000,0.1,1.999);
	dummy->GetXaxis()->SetRangeUser(0.01,1.999);
	dummy->GetYaxis()->SetRangeUser(0.986,1.139);
	dummy->GetXaxis()->SetNdivisions(505);
	dummy->GetYaxis()->SetNdivisions(505);
	dummy->GetXaxis()->SetLabelSize(0.06);
	if(icol==2){
	    dummy->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	    dummy->GetXaxis()->SetTitleSize(0.06);
	    dummy->GetXaxis()->SetTitleOffset(0.8);
	    dummy->GetYaxis()->SetLabelSize(0.06);
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

	dummy->Draw("same");
 
	TLine* line=new TLine(0.25,1,1.999,1);
 	line->SetLineColor(kMagenta);
	line->SetLineStyle(8);
	line->Draw("same");


	TH1F* plot[3];
	for(int ipart=0;ipart<3;ipart++){
	    plot[ipart]=(TH1F*)hist.spec[ipart][cent_select[icol]][0]->Clone();//Negative particles
	    plot[ipart]->SetLineColor(colors[ipart*2]);
	    plot[ipart]->SetMarkerColor(colors[ipart*2]);
	    plot[ipart]->SetMarkerStyle(markers[ipart*2]);
//	    plot[ipart]->Draw("same");
	}
	if(icol==2){
	    TLegend* lg=new TLegend(0.05*(1-hori_margin)+hori_margin,0.7+0.3*vert_margin,0.6+0.4*hori_margin,0.9+0.1*vert_margin);
	    for(int ipart=0;ipart<3;ipart++){
//		int icent=cent_select[icol];
		lg->AddEntry(plot[ipart],species[0][ipart].c_str());
	    }
	    lg->SetBorderSize(0);
	    lg->SetNColumns(3);
	    lg->Draw();
	}

	
	for(int ipart=0;ipart<3;ipart++){
	    plot[ipart]->Draw("same");
	}

	double xlabel,ylabel;
	if(icol%2) xlabel=0.8*(1-vert_margin);
	else xlabel=vert_margin+0.8*(1-vert_margin);
	if(icol==0)ylabel=0.9*(1-hori_margin);
	if(icol==1)ylabel=hori_margin+0.9*(1-hori_margin)*(1-hori_margin);
	if(icol==2)ylabel=hori_margin+0.9*(1-hori_margin);
	int icent=cent_select[icol];
	species_label.DrawLatex(xlabel,ylabel,Form("%i%%-%i%%",cent_tag[icent],cent_tag[icent+1]));
    }
    
    TLatex prelim_tag;
    prelim_tag.SetTextAlign(23);
    prelim_tag.SetTextFont(22);
    prelim_tag.SetTextSize(0.07);
    prelim_tag.SetNDC();
    
    pad[0][0]->cd();
    prelim_tag.DrawLatex(0.5,0.95*(1-vert_margin),"STAR #bf{#it{Preliminary}}");
    prelim_tag.DrawLatex(0.5,0.85*(1-vert_margin),"Isobar #sqrt{s_{NN}}=200 GeV");
    prelim_tag.DrawLatex(0.5,0.75*(1-vert_margin),"-0.5<y<0.5");
//    pad[0][1]->cd();
    prelim_tag.DrawLatex(0.5,0.67*(1-vert_margin),"#bf{statistical uncertainty only}");
    
/*

    for(int icol=0;icol<3;icol++){
	
	double left_edge=margin/2+(1-margin)*icol/3;
	double right_edge=margin/2+(1-margin)*(icol+1)/3;
	if(icol==0)left_edge=0;
	if(icol==2)right_edge=1;
	double pad_margin=(margin/2)/( (1-margin)/3 + margin/2);

	pad[1][icol]=new TPad(Form("Pad_1_%i",icol),"",left_edge,0,right_edge,0.5);
	if(icol==0){
	    pad[1][icol]->SetLeftMargin(pad_margin);
	}
	else pad[1][icol]->SetLeftMargin(0);
	if(icol==2){
	    pad[1][icol]->SetRightMargin(pad_margin);
	}
	else{
	    pad[1][icol]->SetTicky();
	    pad[1][icol]->SetRightMargin(0);
	}
	pad[1][icol]->SetTopMargin(0.03);
	pad[1][icol]->SetBottomMargin(0.12);
	c1->cd();
	pad[1][icol]->Draw();
	pad[1][icol]->cd();


	TH1F* dummy=new TH1F(Form("dummy_1_%i",icol),"",1000,0.1,1.999);
	dummy->GetXaxis()->SetRangeUser(0.01,1.999);
	dummy->GetYaxis()->SetRangeUser(0.9801,1.0199);
	dummy->GetXaxis()->SetNdivisions(505);
	dummy->GetYaxis()->SetNdivisions(505);
	dummy->GetXaxis()->SetLabelSize(0.06);
	if(icol==2){
	    dummy->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	    dummy->GetXaxis()->SetTitleSize(0.06);
	    dummy->GetXaxis()->SetTitleOffset(0.8);
	}
	if(icol==0){
	    dummy->GetYaxis()->SetLabelSize(0.05);
	    dummy->GetYaxis()->SetTitle("Ru+Ru/Zr+Zr ratio");
	    dummy->GetYaxis()->SetTitleSize(.06);
	    dummy->GetYaxis()->SetTitleOffset(1.2);
	}

	dummy->Draw("same");
 
	TLine* line=new TLine(0.25,1,1.999,1);
 	line->SetLineColor(kMagenta);
	line->SetLineStyle(8);
	line->Draw("same");


    }

*/
    c1->Draw();
    c1->SaveAs("Yang_PID_plot_centrality.pdf");
}
