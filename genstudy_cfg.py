import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'dcache:/pnfs/cms/WAX/resilient/sckao/GMSB_FastSim/GMSB_L100_CTau250_1.root',
        'dcache:/pnfs/cms/WAX/resilient/sckao/GMSB_FastSim/GMSB_L100_CTau250_2.root'
    )
)
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')


process.ana = cms.EDAnalyzer('GenStudy',

   genParticles = cms.InputTag("genParticles"),
   rootFileName = cms.untracked.string('genscan250.root'),
   tau          = cms.double( 250 ) 

)


process.p = cms.Path(process.ana)
