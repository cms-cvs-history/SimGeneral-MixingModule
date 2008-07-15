# The following comments couldn't be translated into the new config version:

#
# this is an example of how to run a mix job, with 4 sources, 
# preparing for playback
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("PRODMIX")
process.load("SimGeneral.MixingModule.mixLowLumPU_4sources_cfi")

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    moduleSeeds = cms.PSet(
        mix = cms.untracked.uint32(12345)
    )
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/cms/store/mc/2007/12/2/RelVal-RelValSingleElectronPt35-1196631782/0000/52388364-7CA1-DC11-A0B9-003048562A9E.root')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)
process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *_*_*_*', 
        'keep *_*_*_PRODMIX', 
        'keep PSimHits*_*_*_*', 
        'keep PCaloHits*_*_*_*', 
        'keep SimTracks*_*_*_*', 
        'keep SimVertexs*_*_*_*', 
        'keep edmHepMCProduct_*_*_*'),
    fileName = cms.untracked.string('file:Cum_store_4s.root')
)

process.MessageLogger = cms.Service("MessageLogger",
    debugModules = cms.untracked.vstring('mix'),
    cout = cms.untracked.PSet(
        threshold = cms.untracked.string('DEBUG'),
        DEBUG = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        MixingModule = cms.untracked.PSet(
            limit = cms.untracked.int32(100000)
        )
    ),
    categories = cms.untracked.vstring('MixingModule'),
    destinations = cms.untracked.vstring('cout')
)

process.p = cms.Path(process.mix)
process.outpath = cms.EndPath(process.out)

