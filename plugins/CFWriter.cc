// File: CFWriter.cc
// Description:  see CFWriter.h
// Author:  Emilia Becheva, LLR Palaiseau
//
//--------------------------------------------

#include "SimGeneral/MixingModule/plugins/CFWriter.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/Utilities/interface/Algorithms.h"
#include "FWCore/Utilities/interface/TypeID.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Provenance/interface/Provenance.h"
#include "DataFormats/Provenance/interface/BranchDescription.h"
#include "FWCore/Framework/interface/TriggerNamesService.h"

#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/PCrossingFrame.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/Services/src/Memory.h"


namespace edm 
{
CFWriter::CFWriter(const edm::ParameterSet& iConfig)
: flagSimTrack_(false), 
  flagSimVertex_(false), 
  flagHepMCProduct_(false),  
  flagPCaloHit_(false),
  flagPSimHit_(false)
{ 
  
  //register your products
  ParameterSet ps=iConfig.getParameter<ParameterSet>("mixObjects");
  std::vector<std::string> names = ps.getParameterNames();
  for (std::vector<std::string>::iterator it=names.begin();it!= names.end();++it)
  {
    ParameterSet pset=ps.getParameter<ParameterSet>((*it));
    if (!pset.exists("type"))  continue; //to allow replacement by empty pset

    std::string object = pset.getParameter<std::string>("type");
    std::vector<InputTag>  tags=pset.getParameter<std::vector<InputTag> >("input");
    
    //SimTracks
    if (object=="SimTrack") {
      flagSimTrack_ = true;
      
      InputTag tag;
      if (tags.size()>0) tag=tags[0];
      std::string label;      
      branchesActivate(TypeID(typeid(std::vector<SimTrack>)).friendlyClassName(),std::string(""),tag,label);
      produces<PCrossingFrame<SimTrack> >(label);
      LogInfo("MixingModule") <<"Add PCrossingFrame<SimTrack> "<<object<<"s with InputTag= "<<tag.encode()<<", label will be "<<label;
      
     } 
    //SimVertices
    else if (object=="SimVertex") {
      flagSimVertex_ = true;
      
      InputTag tag;
      if (tags.size()>0) tag=tags[0];
      std::string label;             
      branchesActivate(TypeID(typeid(std::vector<SimVertex>)).friendlyClassName(),std::string(""),tag,label);
      produces<PCrossingFrame<SimVertex> >(label);
      LogInfo("MixingModule") <<"Add SimVertexContainer "<<object<<"s with InputTag= "<<tag.encode()<<", label will be "<<label;
     
    }  
    // PCaloHit
    else if (object=="PCaloHit"){
      flagPCaloHit_ = true; 
      	      
      std::vector<std::string> subdets=pset.getParameter<std::vector<std::string> >("subdets");
      for (unsigned int ii=0;ii<subdets.size();ii++) {
	InputTag tag;
	if (tags.size()==1) tag=tags[0];
        else if(tags.size()>1) tag=tags[ii];
	std::string label;

	branchesActivate(TypeID(typeid(std::vector<PCaloHit>)).friendlyClassName(),subdets[ii],tag,label);
	produces<PCrossingFrame<PCaloHit> >(label);
	LogInfo("MixingModule") <<"Add PCrossingFrame<PCaloHit> "<<object<<"s with InputTag= "<<tag.encode()<<", label will be "<<label;
	 
	// fill table with labels
	labCaloHit.push_back(label);
      }	      
    }
    
    // PSimHit
    else if (object=="PSimHit"){
      flagPSimHit_ = true;
      
      std::vector<std::string> subdets=pset.getParameter<std::vector<std::string> >("subdets");
      for (unsigned int ii=0;ii<subdets.size();ii++) {
	InputTag tag;
	if (tags.size()==1) tag=tags[0];
        
	else if(tags.size()>1) tag=tags[ii];
	std::string label;
	
	branchesActivate(TypeID(typeid(std::vector<PSimHit>)).friendlyClassName(),subdets[ii],tag,label);
	produces<PCrossingFrame<PSimHit> >(label);
	LogInfo("MixingModule") <<"Add PSimHitContainer "<<object<<"s with InputTag= "<<tag.encode()<<", label will be "<<label;
	
	// fill table with labels
	labSimHit.push_back(label);
      } //end for  
    }
    
    // HepMCProduct
    else if (object=="HepMCProduct"){
      flagHepMCProduct_ = true;      
      
      InputTag tag;
      if (tags.size()>0) tag=tags[0];
      std::string label;

      branchesActivate(TypeID(typeid(HepMCProduct)).friendlyClassName(),std::string(""),tag,label);
      produces<PCrossingFrame<edm::HepMCProduct> >(label);
      LogInfo("MixingModule") <<"Add HepMCProduct "<<object<<"s with InputTag= "<<tag.encode()<<", label will be "<<label;      
    }  
    else LogWarning("MixingModule") <<"You did not mix a type of object("<<object<<").";
 
  }//end for 
}


void CFWriter::beginRun(const edm::Run & run,edm::EventSetup const& setup){
}


void CFWriter::beginJob(edm::EventSetup const& setup){
}


CFWriter::~CFWriter(){}


void CFWriter::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{ 
    
  if (flagSimTrack_){
      
    edm::Handle<CrossingFrame<SimTrack> > cf_simtrack;
    iEvent.getByLabel("mix","g4SimHits",cf_simtrack);
  
    PCrossingFrame<SimTrack> * PCFbis = new PCrossingFrame<SimTrack>(*cf_simtrack.product());
    
    std::auto_ptr<PCrossingFrame<SimTrack> > pOutTrack(PCFbis);    
    iEvent.put(pOutTrack,"g4SimHits");

  }//end if flagSimTrack_
  
    //SimVertex
  if (flagSimVertex_){
    edm::Handle<CrossingFrame<SimVertex> > cf_simvtx;
    iEvent.getByLabel("mix","g4SimHits",cf_simvtx);
  
    PCrossingFrame<SimVertex> * PCFvtx = new PCrossingFrame<SimVertex>(*cf_simvtx.product());
    
    std::auto_ptr<PCrossingFrame<SimVertex> > pOutVertex(PCFvtx);    
    iEvent.put(pOutVertex,"g4SimHits");
  }
   
  // PCaloHit
  if (flagPCaloHit_){  
  
    for (unsigned int ii=0;ii<labCaloHit.size();ii++){
      edm::Handle<CrossingFrame<PCaloHit> > cf_calohit;
      iEvent.getByLabel("mix",labCaloHit[ii],cf_calohit);
    
      PCrossingFrame<PCaloHit> * PCFPhCaloHit = new PCrossingFrame<PCaloHit>(*cf_calohit.product()); 
      std::auto_ptr<PCrossingFrame<PCaloHit> > pOutHCalo(PCFPhCaloHit);
      
      iEvent.put(pOutHCalo,labCaloHit[ii]); 
    }
  
  }
  
   if (flagPSimHit_){

    for (unsigned int ii=0;ii<labSimHit.size();ii++) {
     
      edm::Handle<CrossingFrame<PSimHit> > cf_simhit;
      iEvent.getByLabel("mix",labSimHit[ii],cf_simhit);
      
      PCrossingFrame<PSimHit> * PCFSimHit = new PCrossingFrame<PSimHit>(*cf_simhit.product());
      std::auto_ptr<PCrossingFrame<PSimHit> > pOutSimHit(PCFSimHit);
      
      iEvent.put(pOutSimHit,labSimHit[ii]);           
    }    
  }
  
  
  //HepMCProduct 
  if (flagHepMCProduct_){
   
    edm::Handle<CrossingFrame<edm::HepMCProduct> > cf_hepmc;
    iEvent.getByLabel("mix","generator",cf_hepmc);
  
    PCrossingFrame<edm::HepMCProduct> * PCFHepMC = new PCrossingFrame<edm::HepMCProduct>(*cf_hepmc.product());
    std::auto_ptr<PCrossingFrame<edm::HepMCProduct> > pOuthepmcpr(PCFHepMC);
    iEvent.put(pOuthepmcpr,"generator");
  }// end if flagHepMCProduct_
            
}


void CFWriter::branchesActivate(const std::string &friendlyName, std::string subdet, InputTag &tag,std::string &label) {
       
  label=tag.label()+tag.instance();
  wantedBranches_.push_back(friendlyName + '_' +
			      tag.label() + '_' +
			      tag.instance());
        				  
  //if useCurrentProcessOnly, we have to change the input tag
  if (useCurrentProcessOnly_) {
    const std::string processName = edm::Service<edm::service::TriggerNamesService>()->getProcessName();
    tag = InputTag(tag.label(),tag.instance(),processName);
  }    
    
}

}//edm
