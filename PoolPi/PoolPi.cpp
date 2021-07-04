#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;



// ball with wait of 1 and speed of one hit a ball with weight 1 speed one
// eng of ball a is 1 and ball be is 0
// 

class pool_ball
{
private:
    double Weight;
    double Momentum;
    double AllWeight;
    double ShareBump;

public:
    //Initialization: Weight of the pool_ball; Momentum of the pool_ball; AllWeight of both pool_ball; ShareBump if the total bump
    pool_ball(double w, double m, double a) :Weight(w), Momentum(m), AllWeight(a), ShareBump(a - w)
    {

    }
    void test()
    {
        cout << "For Testing";
    };
    //Original function.  As TotalWeight and Weight were fixed after initialization.
    //Overloaded function
    void knock(double TotalWeight, double MomentumKnock, bool SmallBall)
    {
        double knock = ((MomentumKnock / TotalWeight) * (TotalWeight - Weight));
        if (SmallBall == true)
        {
            Momentum -= knock;
        }
        else
        {
            Momentum += knock;
        }
    };
    //Overloaded function
    void knock(double MomentumKnock, bool SmallBall)
    {
        double knock = ((MomentumKnock / AllWeight) * (ShareBump));
        if (SmallBall == true)
        {
            Momentum -= knock;
        }
        else
        {
            Momentum += knock;
        }
    };
    //Flip Momentum
    //Overloaded function
    void knock()

    {
        Momentum = Momentum * -1;
    };
    double GetMomentum()
    {
        return Momentum;
    }
};


int main()
{
    double Momentum = 1;
    double BigWeight;

    BigWeight = 100000000;

    pool_ball ii(1, 0, 1 + BigWeight);
    pool_ball xx(BigWeight, -Momentum, 1 + BigWeight);

    int n = 0;
    int y = 0;
    int ya[8] = {0,0,0,0,0,0,0,0};
    int i = 0; 
    ya[i] = Momentum;

    cout << "Progam Is about to start.\nPlease Wait...";

    while (xx.GetMomentum() < ii.GetMomentum())
        //for(int n = 0; n < 10; n++)
    {
        xx.knock(Momentum * 2, false);
        ii.knock(Momentum * 2, true);
        n++;
        if (ii.GetMomentum() < 0)
        {
            ii.knock();
            n++;
        }
        Momentum = ii.GetMomentum() - xx.GetMomentum();
        y++;
        if (y == 2000) 
        {
            i++;
            ya[i] = Momentum;
            y = 0;
            
        }
    }

    cout << "\nProgam has finshed.\nConstructing graph.\nPlease Wait...";
    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    vector<double> xs{0, 4000, 8000, 12000, 16000, 20000, 24000, 28000};
    vector<double> ys(begin(ya), end(ya));

    ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &xs;
    series->ys = &ys;
    series->linearInterpolation = true;
    series->lineType = toVector(L"dashed");
    series->lineThickness = 2;
    series->color = GetGray(0.3);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 600;
    settings->height = 400;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = toVector(L"PoolPi");
    settings->xLabel = toVector(L"Number Of Knocks");
    settings->yLabel = toVector(L"Momentum");
    settings->scatterPlotSeries->push_back(series);

    DrawScatterPlotFromSettings(imageReference, settings);

    vector<double>* pngdata = ConvertToPNG(imageReference->image);
    WriteToFile(pngdata, "MomentumGraphs.png");
    DeleteImage(imageReference->image);

    cout << "\n\nPoolPi Count:" << n <<"\n\nAny Key Followed By Enter To End Program\n:";
    string f;
    cin >> f;
 
}