#pragma once // it tells the compiler to 
// include a header file only once per compilation
// regardless how many times it is referencedd by #include
#include <vector>
#include <stdexcept>

class Membrane{

    private:
    double width;
    double length;
    
    double tension;
    double surface_mass_density;

    int gridLength;
    int gridWidth;

    std::vector<std::vector<double>> displacement; // 2D vector to store the displacement values of the membrane



    public:
    
    double getWidth() const;
    double getLength() const;
    double getTension() const;
    double getSMD() const;
    int getGridLength() const;
    int getGridWidth() const;
   

    void setWidth(double width);
    void setLength(double length);
    void setTension(double tension);
    void setSMD(double surface_mass_density);
    // void setGridLength(int gridLength);
    // void setGridWidth(int gridWidth);

  

    // constructor of the membrane
    Membrane(double width, double length, double tension, double surface_mass_density, int gridLength, int gridWidth)
    
     : width(width),
        length(length),
        tension(tension),
        surface_mass_density(surface_mass_density),
        gridLength(gridLength),
        gridWidth(gridWidth)
        {
        
        if(width <=0 || length <=0 || tension <=0 || surface_mass_density <= 0 || gridLength <= 0 || gridWidth <=0){
            throw std::invalid_argument("invalid argument(s)");
        }
       
        displacement.resize(gridLength, std::vector<double>(gridWidth, 0.0));

    }

    double getDisplacement(int x, int y) const;
    void setDisplacement(int x, int y, double value);
    
    // wave speed determiens how quickly a disturbance travels
    // actoss the membrane
    double waveSpeed() const;

};