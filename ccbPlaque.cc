/* GEANT4 application for calculating a depth dose profile of the CCB-type ruthenium eye plaque
 * Geometrical description from ICRU 72 Report
 * Physics list based on GEANT4 example "medical/electronScattering2/src/PhysicsList.cc"
 * Developed with GEANT4 version 10.2 patch1 http://geant4.web.cern.ch/geant4/license/LICENSE.html 
 */ 

#ifdef G4MULTITHREADED
    #include "G4MTRunManager.hh"
#else
    #include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
    G4UIExecutive* ui = 0;

    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }

    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4int seconds =  time(NULL);
    G4Random::setTheSeed(seconds);

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(4);
#else
    G4RunManager* runManager = new G4RunManager;
#endif

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserInitialization(new ActionInitialization());

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( !ui )
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else
    {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
}
