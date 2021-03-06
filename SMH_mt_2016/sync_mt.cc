#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "makeHisto.h"
#include "mutau_Tree_mt.h"

int main(int argc, char** argv) {

    using namespace std;
    myMap1 = new map<string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    string status_sample = *(argv + 1);
    bool isMC = false;
    bool isData = false;
    if (status_sample.compare("mc") == 0) isMC = true;
    if (status_sample.compare("data") == 0) isData = true;
    string out = *(argv + 2);
    string outname= out;
    TFile *fout = TFile::Open(outname.c_str(), "RECREATE");

    string in = *(argv + 3);
    string inname= in;
    TFile *fIn = TFile::Open(inname.c_str());

    int recoil=0;
    string recoilType = *(argv + 4);
    if (recoilType.compare("W") == 0)  recoil=1;
    if (recoilType.compare("Z") == 0)  recoil=2;

    TTree* treePtr = (TTree*) fIn->Get("mt/final/Ntuple");
    TH1F *evCounter = (TH1F*) fIn->Get("mt/eventCount");
    TH1F *evCounterW = (TH1F*) fIn->Get("mt/summedWeights");
    HTauTauTree_mt* tree = new HTauTauTree_mt (treePtr);

    TTree *Run_Tree = new TTree("mutau_tree", "mutau_tree");
    Run_Tree->SetDirectory(0);
    Run_Tree->Branch("run", &run, "run/I");
    Run_Tree->Branch("lumi", &lumi, "lumi/I");
    Run_Tree->Branch("evt", &evt, "evt/I");

    Run_Tree->Branch("genpX", &genpX, "genpX/F");
    Run_Tree->Branch("genpY", &genpY, "genpY/F");
    Run_Tree->Branch("genM", &genM, "genM/F");
    Run_Tree->Branch("genpT", &genpT, "genpT/F");
    Run_Tree->Branch("vispX", &vispX, "vispX/F");
    Run_Tree->Branch("vispY", &vispY, "vispY/F");

    Run_Tree->Branch("Rivet_VEta", &Rivet_VEta, "Rivet_VEta/F");
    Run_Tree->Branch("Rivet_VPt", &Rivet_VPt, "Rivet_VPt/F");
    Run_Tree->Branch("Rivet_errorCode", &Rivet_errorCode, "Rivet_errorCode/F");
    Run_Tree->Branch("Rivet_higgsEta", &Rivet_higgsEta, "Rivet_higgsEta/F");
    Run_Tree->Branch("Rivet_higgsPt", &Rivet_higgsPt, "Rivet_higgsPt/F");
    Run_Tree->Branch("Rivet_nJets25", &Rivet_nJets25, "Rivet_nJets25/F");
    Run_Tree->Branch("Rivet_nJets30", &Rivet_nJets30, "Rivet_nJets30/F");
    Run_Tree->Branch("Rivet_p4decay_VEta", &Rivet_p4decay_VEta, "Rivet_p4decay_VEta/F");
    Run_Tree->Branch("Rivet_p4decay_VPt", &Rivet_p4decay_VPt, "Rivet_p4decay_VPt/F");
    Run_Tree->Branch("Rivet_prodMode", &Rivet_prodMode, "Rivet_prodMode/F");
    Run_Tree->Branch("Rivet_stage0_cat", &Rivet_stage0_cat, "Rivet_stage0_cat/F");
    Run_Tree->Branch("Rivet_stage1_cat_pTjet25GeV", &Rivet_stage1_cat_pTjet25GeV, "Rivet_stage1_cat_pTjet25GeV/F");
    Run_Tree->Branch("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV, "Rivet_stage1_cat_pTjet30GeV/F");

    Run_Tree->Branch("npv", &npv, "npv/F");
    Run_Tree->Branch("npu", &npu, "npu/F");
    Run_Tree->Branch("L1iso", &L1iso, "L1iso/F");
    Run_Tree->Branch("L1pt", &L1pt, "L1pt/F");

    Run_Tree->Branch("pt_1", &pt_1, "pt_1/F");
    Run_Tree->Branch("phi_1", &phi_1, "phi_1/F");
    Run_Tree->Branch("eta_1", &eta_1, "eta_1/F");
    Run_Tree->Branch("m_1", &m_1, "m_1/F");
    Run_Tree->Branch("e_1", &e_1, "e_1/F");
    Run_Tree->Branch("q_1", &q_1, "q_1/F");
    Run_Tree->Branch("iso_1", &iso_1, "iso_1/F");

    Run_Tree->Branch("pt_2", &pt_2, "pt_2/F");
    Run_Tree->Branch("phi_2", &phi_2, "phi_2/F");
    Run_Tree->Branch("eta_2", &eta_2, "eta_2/F");
    Run_Tree->Branch("m_2", &m_2, "m_2/F");
    Run_Tree->Branch("e_2", &e_2, "e_2/F");
    Run_Tree->Branch("q_2", &q_2, "q_2/F");
    Run_Tree->Branch("l2_decayMode", &l2_decayMode, "l2_decayMode/F");
    Run_Tree->Branch("againstElectronTightMVA6_2", &againstElectronTightMVA6_2, "againstElectronTightMVA6_2/F");
    Run_Tree->Branch("againstElectronVTightMVA6_2", &againstElectronVTightMVA6_2, "againstElectronVTightMVA6_2/F");
    Run_Tree->Branch("againstMuonLoose3_2", &againstMuonLoose3_2, "againstMuonLoose3_2/F");
    Run_Tree->Branch("byVVLooseIsolationMVArun2v2DBoldDMwLT_2", &byVVLooseIsolationMVArun2v2DBoldDMwLT_2, "byVVLooseIsolationMVArun2v2DBoldDMwLT_2/F");
    Run_Tree->Branch("byVLooseIsolationMVArun2v2DBoldDMwLT_2", &byVLooseIsolationMVArun2v2DBoldDMwLT_2, "byVLooseIsolationMVArun2v2DBoldDMwLT_2/F");
    Run_Tree->Branch("byLooseIsolationMVArun2v2DBoldDMwLT_2", &byLooseIsolationMVArun2v2DBoldDMwLT_2, "byLooseIsolationMVArun2v2DBoldDMwLT_2/F");
    Run_Tree->Branch("byMediumIsolationMVArun2v2DBoldDMwLT_2", &byMediumIsolationMVArun2v2DBoldDMwLT_2, "byMediumIsolationMVArun2v2DBoldDMwLT_2/F");
    Run_Tree->Branch("byTightIsolationMVArun2v2DBoldDMwLT_2", &byTightIsolationMVArun2v2DBoldDMwLT_2, "byTightIsolationMVArun2v2DBoldDMwLT_2/F");
    Run_Tree->Branch("byVTightIsolationMVArun2v2DBoldDMwLT_2", &byVTightIsolationMVArun2v2DBoldDMwLT_2, "byVTightIsolationMVArun2v2DBoldDMwLT_2/F");
    Run_Tree->Branch("byVVTightIsolationMVArun2v2DBoldDMwLT_2", &byVVTightIsolationMVArun2v2DBoldDMwLT_2, "byVVTightIsolationMVArun2v2DBoldDMwLT_2/F");
    Run_Tree->Branch("byIsolationMVA3oldDMwLTraw_2", &byIsolationMVA3oldDMwLTraw_2, "byIsolationMVA3oldDMwLTraw_2/F");
    Run_Tree->Branch("decayModeFinding_2", &decayModeFinding_2, "decayModeFinding_2/F");

    Run_Tree->Branch("numGenJets", &numGenJets, "numGenJets/F");
    Run_Tree->Branch("jetPt_2", &jetPt_2, "jetPt_2/F");

    Run_Tree->Branch("Flag_goodVertices", &Flag_goodVertices, "Flag_goodVertices/F");
    Run_Tree->Branch("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter, "Flag_globalSuperTightHalo2016Filter/F");
    Run_Tree->Branch("Flag_eeBadScFilter", &Flag_eeBadScFilter, "Flag_eeBadScFilter/F");
    Run_Tree->Branch("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter, "Flag_ecalBadCalibFilter/F");
    Run_Tree->Branch("Flag_badMuons", &Flag_badMuons, "Flag_badMuons/F");
    Run_Tree->Branch("Flag_duplicateMuons", &Flag_duplicateMuons, "Flag_duplicateMuons/F");
    Run_Tree->Branch("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter, "Flag_HBHENoiseIsoFilter/F");
    Run_Tree->Branch("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter, "Flag_HBHENoiseFilter/F");
    Run_Tree->Branch("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, "Flag_EcalDeadCellTriggerPrimitiveFilter/F");
    Run_Tree->Branch("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter, "Flag_BadPFMuonFilter/F");
    Run_Tree->Branch("Flag_BadChargedCandidateFilter", &Flag_BadChargedCandidateFilter, "Flag_BadChargedCandidateFilter/F");

    Run_Tree->Branch("met", &met, "met/F");
    Run_Tree->Branch("metSig", &metSig, "metSig/F");
    Run_Tree->Branch("metcov00", &metcov00, "metcov00/F");
    Run_Tree->Branch("metcov10", &metcov10, "metcov10/F");
    Run_Tree->Branch("metcov11", &metcov11, "metcov11/F");
    Run_Tree->Branch("metcov01", &metcov01, "metcov01/F");
    Run_Tree->Branch("metphi", &metphi, "metphi/F");
    Run_Tree->Branch("met_py", &met_py, "met_py/F");
    Run_Tree->Branch("met_px", &met_px, "met_px/F");
    Run_Tree->Branch("met_UESUp", &met_UESUp, "met_UESUp/F");
    Run_Tree->Branch("metphi_UESUp", &metphi_UESUp, "metphi_UESUp/F");
    Run_Tree->Branch("met_UESDown", &met_UESDown, "met_UESDown/F");
    Run_Tree->Branch("metphi_UESDown", &metphi_UESDown, "metphi_UESDown/F");

    Run_Tree->Branch("mjj", &mjj, "mjj/F");
    Run_Tree->Branch("mjj_JetRelativeBalUp", &mjj_JetRelativeBalUp, "mjj_JetRelativeBalUp/F");
    Run_Tree->Branch("mjj_JetRelativeBalDown", &mjj_JetRelativeBalDown, "mjj_JetRelativeBalDown/F");
    Run_Tree->Branch("mjj_JetRelativeSampleUp", &mjj_JetRelativeSampleUp, "mjj_JetRelativeSampleUp/F");
    Run_Tree->Branch("mjj_JetRelativeSampleDown", &mjj_JetRelativeSampleDown, "mjj_JetRelativeSampleDown/F");
    Run_Tree->Branch("mjj_JetEta0to3Up", &mjj_JetEta0to3Up, "mjj_JetEta0to3Up/F");
    Run_Tree->Branch("mjj_JetEta0to3Down", &mjj_JetEta0to3Down, "mjj_JetEta0to3Down/F");
    Run_Tree->Branch("mjj_JetEta0to5Up", &mjj_JetEta0to5Up, "mjj_JetEta0to5Up/F");
    Run_Tree->Branch("mjj_JetEta0to5Down", &mjj_JetEta0to5Down, "mjj_JetEta0to5Down/F");
    Run_Tree->Branch("mjj_JetEta3to5Up", &mjj_JetEta3to5Up, "mjj_JetEta3to5Up/F");
    Run_Tree->Branch("mjj_JetEta3to5Down", &mjj_JetEta3to5Down, "mjj_JetEta3to5Down/F");
    Run_Tree->Branch("gen_match_1", &gen_match_1, "gen_match_1/I");
    Run_Tree->Branch("gen_match_2", &gen_match_2, "gen_match_2/I");

    Run_Tree->Branch("nbtag", &nbtag, "nbtag/I");
    Run_Tree->Branch("njets", &njets, "njets/I");
    Run_Tree->Branch("njets_JetRelativeBalUp", &njets_JetRelativeBalUp, "njets_JetRelativeBalUp/I");
    Run_Tree->Branch("njets_JetRelativeBalDown", &njets_JetRelativeBalDown, "njets_JetRelativeBalDown/I");
    Run_Tree->Branch("njets_JetRelativeSampleUp", &njets_JetRelativeSampleUp, "njets_JetRelativeSampleUp/I");
    Run_Tree->Branch("njets_JetRelativeSampleDown", &njets_JetRelativeSampleDown, "njets_JetRelativeSampleDown/I");
    Run_Tree->Branch("njets_JetEta0to3Up", &njets_JetEta0to3Up, "njets_JetEta0to3Up/I");
    Run_Tree->Branch("njets_JetEta0to3Down", &njets_JetEta0to3Down, "njets_JetEta0to3Down/I");
    Run_Tree->Branch("njets_JetEta0to5Up", &njets_JetEta0to5Up, "njets_JetEta0to5Up/I");
    Run_Tree->Branch("njets_JetEta0to5Down", &njets_JetEta0to5Down, "njets_JetEta0to5Down/I");
    Run_Tree->Branch("njets_JetEta3to5Up", &njets_JetEta3to5Up, "njets_JetEta3to5Up/I");
    Run_Tree->Branch("njets_JetEta3to5Down", &njets_JetEta3to5Down, "njets_JetEta3to5Down/I");

    Run_Tree->Branch("jpt_1", &jpt_1, "jpt_1/F");
    Run_Tree->Branch("jeta_1", &jeta_1, "jeta_1/F");
    Run_Tree->Branch("jphi_1", &jphi_1, "jphi_1/F");

    Run_Tree->Branch("jpt_2", &jpt_2, "jpt_2/F");
    Run_Tree->Branch("jeta_2", &jeta_2, "jeta_2/F");
    Run_Tree->Branch("jphi_2", &jphi_2, "jphi_2/F");

    Run_Tree->Branch("bpt_1", &bpt_1, "bpt_1/F");
    Run_Tree->Branch("bflavor_1", &bflavor_1, "bflavor_1/F");
    Run_Tree->Branch("beta_1", &beta_1, "beta_1/F");
    Run_Tree->Branch("bphi_1", &bphi_1, "bphi_1/F");

    Run_Tree->Branch("bpt_2", &bpt_2, "bpt_2/F");
    Run_Tree->Branch("bflavor_2", &bflavor_2, "bflavor_2/F");
    Run_Tree->Branch("beta_2", &beta_2, "beta_2/F");
    Run_Tree->Branch("bphi_2", &bphi_2, "bphi_2/F");

    Run_Tree->Branch("pt_top1", &pt_top1, "pt_top1/F");
    Run_Tree->Branch("pt_top2", &pt_top2, "pt_top2/F");
    Run_Tree->Branch("genweight", &genweight, "genweight/F");

    Run_Tree->Branch("gen_Higgs_pt", &gen_Higgs_pt, "gen_Higgs_pt/F");
    Run_Tree->Branch("gen_Higgs_mass", &gen_Higgs_mass, "gen_Higgs_mass/F");

    Run_Tree->Branch("extramuon_veto", &extramuon_veto, "extramuon_veto/F");
    Run_Tree->Branch("extraelec_veto", &extraelec_veto, "extraelec_veto/F");
    Run_Tree->Branch("dilepton_veto", &dilepton_veto, "dilepton_veto/F");

    Run_Tree->Branch("trg_crossmuon_mu19tau20_singleL1", &trg_crossmuon_mu19tau20_singleL1, "trg_crossmuon_mu19tau20_singleL1/F");
    Run_Tree->Branch("trg_crossmuon_mu19tau20", &trg_crossmuon_mu19tau20, "trg_crossmuon_mu19tau20/F");
    Run_Tree->Branch("trg_singlemuonTk_22_eta2p1", &trg_singlemuonTk_22_eta2p1, "trg_singlemuonTk_22_eta2p1/F");
    Run_Tree->Branch("trg_singlemuonTk_22", &trg_singlemuonTk_22, "trg_singlemuonTk_22/F");
    Run_Tree->Branch("trg_singlemuon_22_eta2p1", &trg_singlemuon_22_eta2p1, "trg_singlemuon_22_eta2p1/F");
    Run_Tree->Branch("trg_singlemuon_22", &trg_singlemuon_22, "trg_singlemuon_22/F");

    int bestEntry=-1;
    ULong64_t evt_now=0;
    ULong64_t evt_before=-1;
    float muiso_before=100;
    float tauiso_before=-1000;
    float mupt_before=0;
    float taupt_before=0;
    plotFill("nevents",0,9,0,9,evCounter->GetBinContent(1));
    plotFill("nevents",1,9,0,9,evCounterW->GetBinContent(1));
    for (int iEntry = 0; iEntry < tree->GetEntries() ; iEntry++)
    {
        float pu=1.0;
        tree->GetEntry(iEntry);
        bool print=false;
        if (iEntry % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d ", iEntry);
        fflush(stdout);
        plotFill("pileup_mc",tree->nTruePU,80,0,80);
        TLorentzVector dau1;
        TLorentzVector dau2;
        dau1.SetPtEtaPhiM(tree->mPt,tree->mEta,tree->mPhi,tree->mMass);
        dau2.SetPtEtaPhiM(tree->tPt,tree->tEta,tree->tPhi,tree->tMass);
        if (isMC && tree->tZTTGenMatching==5 && tree->tDecayMode==0) dau2=dau2*0.994;
        else if (isMC && tree->tZTTGenMatching==5 && tree->tDecayMode==1) dau2=dau2*0.995;
        else if (isMC && tree->tZTTGenMatching==5 && tree->tDecayMode==10) dau2=dau2*1.000;
        //if (isMC && (tree->tZTTGenMatching==1 or tree->tZTTGenMatching==3) && tree->tDecayMode==0) dau2=dau2*1.000;
        //else if (isMC && (tree->tZTTGenMatching==1 or tree->tZTTGenMatching==3) && tree->tDecayMode==1) dau2=dau2*1.095;
        if (isMC && (tree->tZTTGenMatching==2 or tree->tZTTGenMatching==4) && tree->tDecayMode==0) dau2=dau2*0.998;
        else if (isMC && (tree->tZTTGenMatching==2 or tree->tZTTGenMatching==4) && tree->tDecayMode==1) dau2=dau2*1.015;
        if (dau1.DeltaR(dau2)<0.5) continue;
	if (fabs(tree->mPVDXY)>0.045) continue;
        if (fabs(tree->mPVDZ)>0.2) continue;
        if (fabs(tree->tPVDZ)>0.2) continue;
	if (dau1.Pt()<20 or dau2.Pt()<20) continue;
        if (fabs(dau1.Eta())>2.1 or fabs(dau2.Eta())>2.3) continue;
        if (!tree->tRerunMVArun2v2DBoldDMwLTVVLoose) continue;
	if (!tree->tDecayModeFinding) continue;
	if (!tree->mPFIDMedium) continue;
	evt_now=tree->evt;
	if (evt_now!=evt_before){
	   mupt_before=tree->mPt;
	   muiso_before=tree->mRelPFIsoDBDefault;
	   taupt_before=tree->tPt;
	   tauiso_before=tree->tRerunMVArun2v2DBoldDMwLTraw;
	}
        if (evt_now!=evt_before){
           if (bestEntry>-1){
              fillTree(Run_Tree,tree,bestEntry,recoil,isMC);
           }
	   bestEntry=iEntry;
	}
	if (evt_now==evt_before){
	   if (tree->mRelPFIsoDBDefault<muiso_before or (tree->mRelPFIsoDBDefault==muiso_before && tree->mPt>mupt_before) or (tree->mRelPFIsoDBDefault==muiso_before && tree->mPt==mupt_before && tree->tRerunMVArun2v2DBoldDMwLTraw>tauiso_before) or (tree->mRelPFIsoDBDefault==muiso_before && tree->mPt==mupt_before && tree->tRerunMVArun2v2DBoldDMwLTraw==tauiso_before && tree->tPt>taupt_before) ){
		bestEntry=iEntry;
	        muiso_before=tree->mRelPFIsoDBDefault;
		mupt_before=tree->mPt;
		tauiso_before=tree->tRerunMVArun2v2DBoldDMwLTraw;
		taupt_before=tree->tPt;
	   }
	}
	evt_before=evt_now;
    }
    if (bestEntry>-1)
       fillTree(Run_Tree,tree,bestEntry,recoil,isMC);
    fout->cd();
    Run_Tree->Write();
    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();
    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();

    fout->Close();
    return 0;
}

