int colors[20]={1,879,600,418,632,3,9,20,30,40,810,397,434,844,618,624,797,38,46,43};
int markers[20]={20,21,22,47,29,33,34,37,39,43,45,46,23,48,49,33,34,2,3,5};

class PID_hist{
public:
    TH1F* spec[3][5][2];
public:
    PID_hist(const string file_name);
    virtual ~PID_hist();    
};



PID_hist::PID_hist(const string file_name){
    TFile* inputfile=new TFile(file_name.c_str());
    for(int ipar=0;ipar<3;ipar++){
	for(int icent=0;icent<5;icent++){
	    for(int ich=0;ich<2;ich++){
	    	spec[ipar][icent][ich]=(TH1F*)inputfile->Get(Form("h_RuZrpar%i_midRap_cent%i_ch%i",ipar,4-icent,ich));
//	    	if(ipar==1) spec[ipar][icent][ich]->SetBinContent(2,0);
	    	if(ipar==2) spec[ipar][icent][ich]->SetBinContent(6,0);
	    }
	}
    }
};

PID_hist::~PID_hist(){
    return;
}
