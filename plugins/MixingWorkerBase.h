#ifndef MixingWorkerBase_h
#define MixingWorkerBase_h

/** \class MixingWorkerBase
 *
 * MixingWorkerBase is an auxiliary class for the MixingModule
 *
 * \author Ursula Berthon, LLR Palaiseau
 *
 * \version   1st Version JMarch 2008

 *
 ************************************************************/

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Selector.h"
#include "Mixing/Base/interface/PileUp.h"
#include "DataFormats/Provenance/interface/EventID.h"

//#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/Framework/interface/Selector.h"

//#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
//FIXME????
/* #include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h" */
/* #include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h" */
/* #include "SimDataFormats/Track/interface/SimTrackContainer.h" */
/* #include "SimDataFormats/Vertex/interface/SimVertexContainer.h" */
/* #include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h" */

//#include "DataFormats/Provenance/interface/ProductID.h"
//#include "DataFormats/Common/interface/Handle.h"

//#include <vector>
//#include <string>

namespace edm
{
  class MixingModule;

  class MixingWorkerBase 
    {
    public:

      /** standard constructor*/
      explicit MixingWorkerBase():
	minBunch_(-5), 
	maxBunch_(3),
	bunchSpace_(75),
	subdet_(std::string(" ")),
	label_(std::string(" ")),
	maxNbSources_(5),
 	isTracker_(false)
	{
	  tag_=InputTag();
	  opp_=InputTag();
	}
  
      /*Normal constructor*/ 
      MixingWorkerBase(int minBunch,int maxBunch,int bunchSpace,std::string &subdet, std::string& label,unsigned int maxNbSources,InputTag &tag,bool isTracker);

      /**Default destructor*/
      virtual ~MixingWorkerBase();
      virtual void put(edm::Event &e) =0;
      virtual void createnewEDProduct()=0; 
      virtual void addSignals(const edm::Event &e) =0;
      virtual void addPileups(const int bcr, edm::Event*,unsigned int EventNr,int &vertexOffset=0)=0;
      virtual void setBcrOffset()=0;
      virtual void setSourceOffset(const unsigned int s)=0;
      virtual void setOppositeTag(InputTag& opp) {opp_=opp;}
      virtual void setCheckTof(bool checktof) {checktof_=checktof;}
   
    protected:
      int const minBunch_;
      int const maxBunch_;
      int const bunchSpace_;
      std::string const subdet_;
      std::string const label_;
      unsigned int const maxNbSources_;
      InputTag tag_;
      bool isTracker_;
      bool checktof_;
      InputTag opp_;

    private:
      unsigned int eventNr_;

    };
}//edm

#endif