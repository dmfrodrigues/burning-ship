#ifndef BURNINGSHIP_H_INCLUDED
#define BURNINGSHIP_H_INCLUDED

#include "FractalBitmap.h"

#include <deque>
#include <vector>
#include <list>

class bs: public FractalBitmap{
private:
    ///PRIVATE TYPEDEFS
    typedef float ColorT;

    ///PRIVATE STATIC CONSTANTS
    static constexpr ColorT cycle = 200.0L; /*100.0*/                 ///number of colors in a cycle (for coloring)
    static constexpr ColorT pi = 3.1415926535897L; //acos(-1.0L);
    static constexpr ColorT pi_2 = pi*0.5L;
    static constexpr ColorT pi2 = 2.0L*pi;
    static constexpr ColorT pi2_cycle = pi2/cycle;
    static constexpr ColorT omega = pi2_cycle;
    static constexpr ColorT phi = 3.0L*pi_2;
    static constexpr ColorT AMP[] = {+127.0, +127.0, -70.0}, INIT[] = {+127.5, +127.5, +71.0}; ///BLUE&YELLOW
    //static constexpr ColorT AMP[] = {+27.5, +110.0, +110.0}, INIT[] = {+227.5, +110.0, +110.0}; ///RED&WHITE
    //static const ColorT AMP[] = {-100.0, -100.0, +  0.0}, INIT[] = {+101.0, +101.0, +  0.0}; ///YELLOW&BLACK
    //static const ColorT AMP[] = {-107.0, +  0.0, +  0.0}, INIT[] = {+128.0, + 10.0, + 10.0}; ///RED&BLACK
    //static const ColorT AMP[] = {-113.0, -113.0, -113.0}, INIT[] = {+140.0, +140.0, +140.0}; ///BLACK&WHITE
    static const ComplexT bailout;
    static const ComplexT bailout_sqr;
    static constexpr ColorT log10N = 0.90308998699; //log10(bailout);
    static constexpr ColorT log2_log10N = -0.14705834492L; //std::log2(log10N);
    static constexpr unsigned NThreads = 8;

    ///MEMBER VARIABLES
    ComplexT            step;   ///Difference between consecutive pixels
    ComplexNum          origin; ///Upper-left corner
    ComplexNum          center; ///Center of the fractal
    IterationT          numIt=0;///Total number of iterations performed over the fractal
    const IterationT    addIt;
    ComplexNum          *C=NULL, *Z=NULL; ///Point in complex space, current value of z
    IterationT          *IT=NULL;    ///Number of iterations
    std::list<unsigned> *LCHK=NULL;

    wxNativePixelData   px;     ///PixelData, to access bmp

    ///PRIVATE FUNCTIONS
    /**
     * Update pixels in [L,R) by making an additional addIt iterations
     */
    void UpdateMathLim(unsigned index, IterationT addIt, std::deque<unsigned>* changed);
    /**
     * Update pixels whose indexes are in q, based on the information in the variables
     */
    void UpdatePixels(const std::deque<unsigned>& v);
    /**
     * Balance lists
     */
    void BalanceLists();

    static ColorT CycleFun(ColorT x);








public:
    /**
     * Constructor
     */
    bs(IterationT addIter);
    /**
     * New
     */
    void New(ComplexNum o, ComplexT st, wxSize s, bool IsCenter = false);
    /**
     * CreateNew
     */
    bs* CreateNew(ComplexNum o, ComplexT st, wxSize s, bool IsCenter = false) const;
    /**
     * Destructor
     */
    ~bs();

    ///CALCULATIONS ==================================================
    /**
     * Update all pixels by making an additional addIt iterations
     */
    void UpdateMath();

    ///GET FUNCTION ==================================================
    ComplexNum GetOrigin()         const{ return origin; }
    ComplexNum GetCenter()         const{ return center; }
    ComplexT   GetStep()           const{ return step;   }
    ComplexT   GetHorizontalSize() const{ return step*(ComplexT)GetSize().x; }
    IterationT GetNum()            const{ return numIt; }
    IterationT GetCyclesPerRun()   const{ return addIt; }
    IterationT GetNotEscaped()     const;

    ///OTHER UTILITIES
    bool SaveFile(const wxString& name, wxBitmapType type, const wxPalette *palette = NULL) const;
};

#endif
