#include "TRex/TRexColour.hh"

TRexColour* TRexColour::fColour = NULL;

TRexColour* TRexColour::Get() {
  if(fColour == NULL) {
    fColour = new TRexColour();
  }
  return fColour;
}

TRexColour::TRexColour() {
  red        = new G4VisAttributes(true, G4Colour(1.0, 0.0, 0.0));
  darkred    = new G4VisAttributes(true, G4Colour(0.5, 0.0, 0.0));
  orange     = new G4VisAttributes(true, G4Colour(1.0, 0.3, 0.0));
  green      = new G4VisAttributes(true, G4Colour(0.0, 1.0, 0.0));
  darkgreen  = new G4VisAttributes(true, G4Colour(0.0, 0.5, 0.0));
  lightgreen = new G4VisAttributes(true, G4Colour(0.5, 1.0, 0.5));
  blue       = new G4VisAttributes(true, G4Colour(0.0, 0.0, 1.0));
  darkblue   = new G4VisAttributes(true, G4Colour(0.0, 0.0, 0.5));
  lightblue  = new G4VisAttributes(true, G4Colour(0.5, 0.5, 1.0));
  yellow     = new G4VisAttributes(true, G4Colour(1.0, 1.0, 0.0));
  darkyellow = new G4VisAttributes(true, G4Colour(0.8, 0.8, 0.0));
  deepyellow = new G4VisAttributes(true, G4Colour(0.5, 0.5, 0.0));
  magenta    = new G4VisAttributes(true, G4Colour(1.0, 0.0, 1.0));
  cyan       = new G4VisAttributes(true, G4Colour(0.0, 1.0, 1.0));
  darkcyan   = new G4VisAttributes(true, G4Colour(0.0, 0.8, 0.8));
  deepcyan   = new G4VisAttributes(true, G4Colour(0.0, 0.5, 0.5));
  gray       = new G4VisAttributes(true, G4Colour(0.8, 0.8, 0.8));
  lightgray  = new G4VisAttributes(true, G4Colour(0.9, 0.9, 0.9));
  darkgray   = new G4VisAttributes(true, G4Colour(0.5, 0.5, 0.5));
  deepgray   = new G4VisAttributes(true, G4Colour(0.3, 0.3, 0.3));
  floorcolor = new G4VisAttributes(true, G4Colour(0.5, 0.4, 0.2));
  white      = new G4VisAttributes(true, G4Colour(1.0, 1.0, 1.0));
  black      = new G4VisAttributes(true, G4Colour(0.0, 0.0, 0.0));
  invisible  = new G4VisAttributes(false, G4Colour(0.0, 0.0, 0.0));
  silver     = new G4VisAttributes(true, G4Colour(0.75294,0.75294,0.75294));

  red       ->SetForceSolid(true);
  darkred   ->SetForceSolid(true);
  orange    ->SetForceSolid(true);
  green     ->SetForceSolid(true);
  darkgreen ->SetForceSolid(true);
  lightgreen->SetForceSolid(true);
  blue      ->SetForceSolid(true);
  darkblue  ->SetForceSolid(true);
  lightblue ->SetForceSolid(true);
  yellow    ->SetForceSolid(true);
  darkyellow->SetForceSolid(true);
  deepyellow->SetForceSolid(true);
  magenta   ->SetForceSolid(true);
  cyan      ->SetForceSolid(true);
  darkcyan  ->SetForceSolid(true);
  deepcyan  ->SetForceSolid(true);
  gray      ->SetForceSolid(true);
  lightgray ->SetForceSolid(true);
  darkgray  ->SetForceSolid(true);
  deepgray  ->SetForceSolid(true);
  floorcolor->SetForceSolid(true);
  white     ->SetForceSolid(true);
  black     ->SetForceSolid(true);
  invisible ->SetForceSolid(true);
  silver    ->SetForceSolid(true);
}
