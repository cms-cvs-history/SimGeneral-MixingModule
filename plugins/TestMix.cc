// -*- C++ -*-
//
// Class:      TestMix
// 
/**\class TestMix

 Description: test of Mixing Module

*/
//
// Original Author:  Ursula Berthon
//         Created:  Fri Sep 23 11:38:38 CEST 2005
// $Id: TestMix.cc,v 1.6 2007/11/15 15:10:34 uberthon Exp $
//
//


// system include files
#include <memory>
#include <utility>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"

#include "TestMix.h"

#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"


using namespace edm;

TestMix::TestMix(const edm::ParameterSet& iConfig): 
  level_(iConfig.getUntrackedParameter<int>("PrintLevel"))
{
  std::cout << "Constructed testMix , level "<<level_<<std::endl;

  track_containers_.push_back("TrackerHitsTECHighTof");
  track_containers_.push_back("TrackerHitsTECLowTof");

  track_containers2_.push_back("TrackerHitsTECLowTof");
  track_containers2_.push_back("TrackerHitsTECHighTof");

}


TestMix::~TestMix()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to analyze the data  ------------
void
TestMix::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  // test accesses to CrossingFrame
  // attention: operator-> returns the templated object, but
  // bunch() and getTrigger() are methods of the iterator itself!

  // test access to SimTracks directly in CrossingFrame

  edm::Handle<CrossingFrame<SimTrack> > cf_simtrack;
  iEvent.getByLabel("mix",cf_simtrack);

  std::vector<SimTrack>::const_iterator first;
  std::vector<SimTrack>::const_iterator last;
  cf_simtrack->getPileups(first,last);
  unsigned int ic=0;
  for (std::vector<SimTrack>::const_iterator it=first;it!=last;it++) {
    //    std::cout<<" pileup SimTrack "<<ic<<" has genpart index  "<<(*it).genpartIndex()<<" vertex Index "<<(*it).vertIndex()  <<" bunchcrossing "<<cf_simtrack->getBunchCrossing(ic)<<std::endl;
    ic++;
  }


  const std::string subdet("TrackerHitsTECHighTof");
  edm::Handle<CrossingFrame<PSimHit> > cf_simhit;
  iEvent.getByLabel("mix",subdet,cf_simhit);
  std::cout<<"\n\n=================== Starting SimHit access, subdet "<<subdet<<"  ==================="<<std::endl;

  std::auto_ptr<MixCollection<PSimHit> > col(new MixCollection<PSimHit>(cf_simhit.product(),std::pair<int,int>(-1,1)));
  std::cout<<*(col.get())<<std::endl;
  MixCollection<PSimHit>::iterator cfi;
  int count=0;
  for (cfi=col->begin(); cfi!=col->end();cfi++) {
    std::cout<<" Hit "<<count<<" has tof "<<cfi->timeOfFlight()<<" trackid "<<cfi->trackId() <<" bunchcr "<<cfi.bunch()<<" trigger "<<cfi.getTrigger()<<", from EncodedEventId: "<<cfi->eventId().bunchCrossing()<<" " <<cfi->eventId().event() <<" bcr from MixCol "<<cfi.bunch()<<std::endl;
    //      std::cout<<" Hit: "<<(*cfi)<<std::endl;
    count++;
  }

  // test access to CaloHits
  const std::string subdetcalo("EcalHitsEB");
  edm::Handle<CrossingFrame<PCaloHit> > cf_calo;
  iEvent.getByLabel("mix",subdetcalo,cf_calo);
  std::cout<<"\n\n=================== Starting CaloHit access, subdet "<<subdetcalo<<"  ==================="<<std::endl;
  std::auto_ptr<MixCollection<PCaloHit> > colcalo(new MixCollection<PCaloHit>(cf_calo.product(), std::pair<int,int>(-1,1)));
  std::cout<<*(colcalo.get())<<std::endl;
  MixCollection<PCaloHit>::iterator cficalo;
  count=0;
  for (cficalo=colcalo->begin(); cficalo!=colcalo->end();cficalo++) {
    std::cout<<" CaloHit "<<count<<" has tof "<<cficalo->time()<<" trackid "<<cficalo->geantTrackId() <<" bunchcr "<<cficalo.bunch()<<" trigger "<<cficalo.getTrigger()<<", from EncodedEventId: "<<cficalo->eventId().bunchCrossing()<<" " <<cficalo->eventId().event() <<std::endl;
    //      std::cout<<" Calo Hit: "<<(*cficalo)<<std::endl;
    count++;
  }

  // test access to SimTracks
  std::cout<<"\n=================== Starting SimTrack access ==================="<<std::endl;
  //   edm::Handle<CrossingFrame<SimTrack> > cf_simtrack;
  //   iEvent.getByLabel("mix",cf_simtrack);
  std::auto_ptr<MixCollection<SimTrack> > col2(new MixCollection<SimTrack>(cf_simtrack.product()));
  MixCollection<SimTrack>::iterator cfi2;
  int count2=0;
  std::cout <<" \nWe got "<<col2->sizeSignal()<<" signal tracks and "<<col2->sizePileup()<<" pileup tracks, total: "<<col2->size()<<std::endl;
  for (cfi2=col2->begin(); cfi2!=col2->end();cfi2++) {
    std::cout<<" SimTrack "<<count2<<" has genpart index  "<<cfi2->genpartIndex()<<" vertex Index "<<cfi2->vertIndex() <<" bunchcr "<<cfi2.bunch()<<" trigger "<<cfi2.getTrigger()<<", from EncodedEventId: "<<cfi2->eventId().bunchCrossing() <<" "<<cfi2->eventId().event() <<std::endl;
    count2++; 
  }

  // test access to SimVertices
  std::cout<<"\n=================== Starting SimVertex access ==================="<<std::endl;
  edm::Handle<CrossingFrame<SimVertex> > cf_simvtx;
  iEvent.getByLabel("mix",cf_simvtx);
  std::auto_ptr<MixCollection<SimVertex> > col3(new MixCollection<SimVertex>(cf_simvtx.product()));
  MixCollection<SimVertex>::iterator cfi3;
  int count3=0;
  std::cout <<" \nWe got "<<col3->sizeSignal()<<" signal vertices and "<<col3->sizePileup()<<" pileup vertices, total: "<<col3->size()<<std::endl;
  for (cfi3=col3->begin(); cfi3!=col3->end();cfi3++) {
    std::cout<<" SimVertex "<<count3<<" has parent index  "<<cfi3->parentIndex()<<" bunchcr "<<cfi3.bunch()<<" trigger "<<cfi3.getTrigger()<<", from EncodedEventId: "<<cfi3->eventId().bunchCrossing() <<" "<<cfi3->eventId().event() <<std::endl;
    count3++; 
  }

  //test MixCollection constructor with several subdetector names
  std::cout<<"\n=================== Starting test for coll of several ROU-s ==================="<<std::endl;
  //    edm::Handle<CrossingFrame<PSimHit> > cf_simhit;
  std::vector<const CrossingFrame<PSimHit> *> cfvec;
  iEvent.getByLabel("mix",track_containers_[0],cf_simhit);
  cfvec.push_back(cf_simhit.product());
  std::cout <<" \nFirst container "<<track_containers_[0]<<" Nr signals "<<cf_simhit->getNrSignals() << ", Nr pileups "<<cf_simhit->getNrPileups() <<std::endl;
  iEvent.getByLabel("mix",track_containers_[1],cf_simhit);
  cfvec.push_back(cf_simhit.product());
  std::cout <<" \nSecond container "<<track_containers_[1]<<" Nr signals "<<cf_simhit->getNrSignals() << ", Nr pileups "<<cf_simhit->getNrPileups() <<std::endl;
  std::auto_ptr<MixCollection<PSimHit> > all_trackhits(new MixCollection<PSimHit>(cfvec));

  std::cout <<" \nFor all containers we got "<<all_trackhits->sizeSignal()<<" signal hits and "<<all_trackhits->sizePileup()<<" pileup hits, total: "<<all_trackhits->size()<<std::endl;
    
  MixCollection<PSimHit>::iterator it;
  int ii=0;
  for (it=all_trackhits->begin(); it!= all_trackhits->end();it++) {
    std::cout<<" Hit "<<ii<<" of all hits has tof "<<it->timeOfFlight()<<" trackid "<<it->trackId() <<" bunchcr "<<it.bunch()<<" trigger "<<it.getTrigger()<<", from EncodedEventId: "<<it->eventId().bunchCrossing() <<" "<<it->eventId().event()<<std::endl;
    ii++;
  }

  //test the same in different order: should be the same sizes, different order
  std::vector<const CrossingFrame<PSimHit> *> cfvec2;
  iEvent.getByLabel("mix",track_containers2_[0],cf_simhit);
  cfvec2.push_back(cf_simhit.product());
  iEvent.getByLabel("mix",track_containers2_[1],cf_simhit);
  cfvec2.push_back(cf_simhit.product());
  std::auto_ptr<MixCollection<PSimHit> > all_trackhits2(new MixCollection<PSimHit>(cfvec2));
  std::cout <<" \nSame containers, different order: we got "<<all_trackhits2->sizeSignal()<<" signal hits and "<<all_trackhits2->sizePileup()<<" pileup hits, total: "<<all_trackhits2->size()<<std::endl;
  MixCollection<PSimHit>::iterator it2;
  int ii2=0;
  for (it2=all_trackhits2->begin(); it2!= all_trackhits2->end();it2++) {
    std::cout<<" Hit "<<ii2<<" of all hits has tof "<<it2->timeOfFlight()<<" trackid "<<it2->trackId() <<" bunchcr "<<it2.bunch()<<" trigger "<<it2.getTrigger()<<", bcr from Id: "<<it2->eventId().bunchCrossing() <<" evtnr in id "<<it2->eventId().event()<<std::endl;
    ii2++;
  }

  //test MixCollection for HepMCProducts
  //------------------------------------
  edm::Handle<CrossingFrame<edm::HepMCProduct> > cf_hepmc;
  iEvent.getByLabel("mix",cf_hepmc);
  std::auto_ptr<MixCollection<edm::HepMCProduct> > colhepmc(new MixCollection<edm::HepMCProduct>(cf_hepmc.product()));
  MixCollection<edm::HepMCProduct>::iterator cfihepmc;
  int counthepmc=0;
  std::cout <<" \nWe got "<<colhepmc->sizeSignal()<<" signal hepmc products and "<<colhepmc->sizePileup()<<" pileup hepmcs, total: "<<colhepmc->size()<<std::endl;
  for (cfihepmc=colhepmc->begin(); cfihepmc!=colhepmc->end();cfihepmc++) {
    std::cout<<" edm::HepMCProduct "<<counthepmc<<" has event number "<<cfihepmc->GetEvent()->event_number()<<", "<< cfihepmc->GetEvent()->particles_size()<<" particles and "<<cfihepmc->GetEvent()->vertices_size()<<" vertices,  bunchcr= "<<cfihepmc.bunch()<<" trigger= "<<cfihepmc.getTrigger() <<" sourcetype= "<<cfihepmc.getSourceType()<<std::endl;
    counthepmc++;
  }

  //----------------------------------------------------------------------------
  //  testing special situations
  //----------------------------------------------------------------------------
 
  // test reusage of the same iterator
  int ii3=0;
  for (it2=all_trackhits2->begin(); it2!= all_trackhits2->end();it2++) ii3++;
  if (ii3!=ii2) std::cout<<" Problem when re-using iterator!!"<<std::endl;
  else  std::cout<<" \nNo problem when re-using iterator."<<std::endl;

  // test access to non-filled collections
  //cases:   0) ok, collection has members
  //         1) bunchrange given outside of existent bunchcrossing numbers ==>exc

  std::cout<<"\n=================== Starting tests for abnormal conditions ==================="<<std::endl;

  // test case 0
  std::cout<<"\n[ Testing abnormal conditions case 0]Should be all ok: registry: "<<all_trackhits->inRegistry()<<" size: "<<all_trackhits->size()<<std::endl;

						// test case 1
						MixCollection<PSimHit> * col21=0;
						try {
						  col21=new MixCollection<PSimHit>(cf_simhit.product(),std::pair<int,int>(-10,20));
						} catch ( cms::Exception &e ) { std::cout<<" [Testing abnormal conditions case2] exception bad runrange ok "<<std::endl; }

}
