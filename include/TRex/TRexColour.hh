#ifndef TREXCOLOUR_HH_
#define TREXCOLOUR_HH_

#include "G4VisAttributes.hh"

class TRexColour
{
  public:
    static TRexColour* Get(void);
    ~TRexColour(void);

    G4VisAttributes* red;
    G4VisAttributes* darkred;
    G4VisAttributes* orange;
    G4VisAttributes* green;
    G4VisAttributes* darkgreen;
    G4VisAttributes* lightgreen;
    G4VisAttributes* blue;
    G4VisAttributes* darkblue;
    G4VisAttributes* lightblue;
    G4VisAttributes* yellow;
    G4VisAttributes* darkyellow;
    G4VisAttributes* deepyellow;
    G4VisAttributes* magenta;
    G4VisAttributes* cyan;
    G4VisAttributes* darkcyan;
    G4VisAttributes* deepcyan;
    G4VisAttributes* gray;
    G4VisAttributes* lightgray;
    G4VisAttributes* darkgray;
    G4VisAttributes* deepgray;
    G4VisAttributes* floorcolor;
    G4VisAttributes* white;
    G4VisAttributes* black;
    G4VisAttributes* invisible;
    G4VisAttributes* silver;

  private:
    TRexColour(void);
    static TRexColour* fColour;
};

#endif /* TREXCOLOUR_HH_ */
