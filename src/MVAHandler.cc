#include "UserCode/bsmhiggs_fwk/interface/MVAHandler.h"

//
MVAHandler::MVAHandler()
{
}

//
MVAEvtContainer &MVAHandler::getEvent()
{
  return evSummary_;
}

//
void MVAHandler::resetStruct()
{
  //catagory type
  evSummary_.is3b = false;
  evSummary_.is4b = false; 
  //W boson related only related var
  evSummary_.WpT = -1.0;
  //Higgs boson related only var
  evSummary_.Hmass = -1.0; 
  evSummary_.HpT = -1.0; 
  evSummary_.bbdRAve = -1.0; 
  evSummary_.bbdMMin = -1.0;
  evSummary_.HHt = -1.0;
  //dr W and Higgs 
  evSummary_.WHdR = -1.0;
  //weight
  evSummary_.weight = 0.0;
  evSummary_.lheNJets = -1;
}

//
void MVAHandler::getEntry( 
                          bool is3b, bool is4b, 
                          float Wpt, //W only
                          float Hmass, float HpT, float bbdRAve, float bbdMMin, float HHt, //Higgs only
                          float WHdR, //W and H
                          float weight,
                          int lheNJets
                         )
{
  resetStruct();
  //catagory type
  evSummary_.is3b = is3b;
  evSummary_.is4b = is4b;
  //W boson related only related var
  evSummary_.WpT = Wpt;
  //Higgs boson related only var
  evSummary_.Hmass = Hmass;
  evSummary_.HpT = HpT;
  evSummary_.bbdRAve = bbdRAve;
  evSummary_.bbdMMin = bbdMMin;
  evSummary_.HHt = HHt;
  //dr W and Higgs 
  evSummary_.WHdR = WHdR;
  //weight
  evSummary_.weight = weight;
  //AUX
  evSummary_.lheNJets = lheNJets;
  return ;
}

//
bool MVAHandler::initTree(TString mvaout)
{
  //write mode, to mva tree
  MVAofile = TFile::Open( mvaout, "recreate");
  to3b = new TTree("TribMVA","TribMVA");
  to4b = new TTree("QuabMVA","QuabMVA");

  to3b->Branch("WpT",  &evSummary_.WpT,  "WpT/F");
  to3b->Branch("Hmass",  &evSummary_.Hmass,  "Hmass/F");
  to3b->Branch("HpT",  &evSummary_.HpT,  "HpT/F");
  to3b->Branch("bbdRAve",  &evSummary_.bbdRAve,  "bbdRAve/F");
  to3b->Branch("bbdMMin",  &evSummary_.bbdMMin,  "bbdMMin/F");
  to3b->Branch("HHt",  &evSummary_.HHt,  "HHt/F");
  to3b->Branch("WHdR",  &evSummary_.WHdR,  "WHdR/F");
  to3b->Branch("weight",  &evSummary_.weight,  "weight/F");
  to3b->Branch("lheNJets",  &evSummary_.lheNJets,  "lheNJets/I");


  to4b->Branch("WpT",  &evSummary_.WpT,  "WpT/F");
  to4b->Branch("Hmass",  &evSummary_.Hmass,  "Hmass/F");
  to4b->Branch("HpT",  &evSummary_.HpT,  "HpT/F");
  to4b->Branch("bbdRAve",  &evSummary_.bbdRAve,  "bbdRAve/F");
  to4b->Branch("bbdMMin",  &evSummary_.bbdMMin,  "bbdMMin/F");
  to4b->Branch("HHt",  &evSummary_.HHt,  "HHt/F");
  to4b->Branch("WHdR",  &evSummary_.WHdR,  "WHdR/F");
  to4b->Branch("weight",  &evSummary_.weight,  "weight/F");
  to4b->Branch("lheNJets",  &evSummary_.lheNJets,  "lheNJets/I");

  return true;
}

//
void MVAHandler::fillTree()
{
  if ( evSummary_.is3b && evSummary_.is4b )
  {
    std::cout << "One event can not be both in 3 and 4 b cat! Please check!" << std::endl;
  }
  else if ( evSummary_.is3b && !evSummary_.is4b )
  {
    if ( to3b ) to3b->Fill();
    return ;
  }
  else if ( !evSummary_.is3b && evSummary_.is4b )
  {
    if ( to4b ) to4b->Fill();
    return ;
  }
  else return ;
  return ;
}

//
void MVAHandler::writeTree()
{
  //TFile *MVAofile=TFile::Open( outURL, "recreate");
  to3b->Write();
  to4b->Write();
  MVAofile->Close();
  return ;
}
//
MVAHandler::~MVAHandler()
{
}
