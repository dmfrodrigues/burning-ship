#include "FractalFrame.h"
#include "BurningShip.h"

class FractalApp: public wxApp{
private:
    FractalFrame *fractalFrame;
    bs *f;
public:
    virtual bool OnInit(){
        wxInitAllImageHandlers();
        f = new bs(200);
        fractalFrame = new FractalFrame(f);
        fractalFrame->Show(true);
        return true;
    }
    int OnExit(){
        delete f;
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(FractalApp);
