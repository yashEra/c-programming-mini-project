#include <stdio.h>
#include <stdlib.h>

///cost of one unit of each material
float cC = 1475;//cement 50Kg bag cost
float sC = 14000;//Sand 1 cube cost
float mC = 8625;//metal 1 cube cost
const float rCt= 254500;//Reinforcement bars 1 ton cost
float rCk= rCt*0.001;//Reinforcement bars 1Kg cost
float firedBrik = 40;//one brick price
float paintC = 4000;//paint 4L bucket price
float fillerC = 900;//filler 4L bucket price
float tileC = 1000;//Tile cost(2x2feet)
float tileMc = 500;//Tile mortar 20Kg bag price
float sheetC = 3520;//35.12 Sq.ft

///Total quantity of each material
float cemenT = 0;
float sandT = 0;
float metalT = 0;
float steelsT = 0;
float firedBriksT = 0;
float paintT = 0;
float fillerT = 0;
float sheetsT = 0;
float tilesT = 0;
float tileMT = 0;

int roofT;
float totalBill = 0;

///function prototype
void choises();///choice house, building or exit
void house();///all house operations
void building();///all building operations
void slabsAndWalls(int);///input all slab and wall details house and different structure building
void columnSame(int);///input all details of column(columns quantity same in each floor)
void columnDif(int);///input all details of column(column quantity different by floor)
void stairs(int);///input all details of stairs
void roofType();///input all details of roof
void columnsCost(double, double);///column cost and materials quantity calculation
void slabsCost(double, double);///slab cost and materials quantity calculation
void wallsCost(double );///wall cost and materials quantity calculation
void stairsCost(double , double );///stairs cost and materials quantity calculation
void slabRoofCost(double , double);///slab roof cost and materials quantity calculation
void tileCost(float);///tile cost and material quantity quantity calculation
void sheetRoofCost(double);///sheet roof floor cost and materials quantity calculation
void gfCost(double, double, double);///ground floor cost and materials quantity calculation
void totalMaterial(int);///final output of the program. the text file of final output create in this function


int main()
{
    char type;

    choises();
    scanf("%c", &type);

    switch (type)
    {
    case 'H':
        house();
        break;
    case 'B':
        building();
        break;
    case 'E':
        puts("Bye!!!");
        exit(0);
        break;
    default:
        printf("\n******* You inputed wrong choice please try again *******\n\n");
        getchar();
        main();
    }
    return (0);
}

void choises()
{
    printf("\n -----> G14 Construction Estimates <-----\n\n");

    puts("\t***************************");
    puts("\t*1. House(H)              *");
    puts("\t*2. Building(B)           *");
    puts("\t*3. Exit(E)               *");
    puts("\t***************************");
    printf("\tEnter your choice <H,B,E>: ");
}

///*****House process*****

void house()
{
    int floor;

    printf("\n--> How many floors in your House : ");
    scanf("%d", &floor);

    if(floor<1)
    {
        printf("\n--> The number of floors in your house could not be less than one.");
        house();
    }

    slabsAndWalls(floor);
    columnDif(floor);
    if (floor > 1)
    stairs(floor);
    roofType();
    totalMaterial(roofT);
}

///*****Building process*****

void building()
{
    int floor;
    float sf_total = 0;
    int floorType;
    float foundation;
    float slabTotArea;
    float slabTotVol = 0;
    int tie;
    float length;
    float cross;

    printf("\n--> How many floors in your building : ");
    scanf("%d", &floor);

    if(floor<1)
    {
        printf("\n--> The number of floors in your building could not be less than one.");
        building();
    }


    puts("\n\t***************************************");
    puts("\t*   Select your building floor type   *");
    puts("\t*1. If same structure each floor      *");
    puts("\t*2. else                              *");
    puts("\t***************************************");
    printf("\tEnter your choice <1 or 2>: ");
    scanf("%d", &floorType);

    if (floorType == 1 || floorType == 2)
    {
        if (floorType == 1)
        {
            float wf;
            float sb;
            float sbThik;
            float sbVol;
            float fCost;

            ///ground floor
            printf("\n--> How many square feet  in structural floor(on ground floor) : ");
            scanf("%f", &foundation);
            printf("--> Enter Your number of Tie Beams : ");
            scanf("%d",&tie);
            printf("--> How many length of Tie Beams (feet) : ");
            scanf("%f",&length);
            float lengthT = length*tie;
            printf("--> How many Cross-sectional area in square feet :");
            scanf("%f",&cross);
            float volT=length*cross*tie;
            system("cls");
            gfCost(volT, length, foundation);

            ///slabs
            if(floor > 1)
            {
                printf("--> How many square feet  in a slab : ");
                scanf("%f", &sb);
                printf("--> How many thickness  in a slab : ");
                scanf("%f", &sbThik);
                sbVol = sb * sbThik;
                slabTotArea = (floor - 1)*sb;
                slabTotVol = (floor - 1) * sbVol;
                system("cls");

                slabsCost(slabTotVol, slabTotArea);
            }
            float totTileCoverage = slabTotArea+foundation;
            tileCost(totTileCoverage);

            ///**********walls**********
            printf("\n--> How many square feet of walls in a floor : ");
            scanf("%f", &wf);
            sf_total = floor * wf;
            system("cls");

            wallsCost(sf_total);

            columnSame(floor);
            if(floor > 1)
            stairs(floor);
            roofType();
            totalMaterial(roofT);
        }
        else
        {
            slabsAndWalls(floor);
            columnDif(floor);
            if(floor > 1)
            stairs(floor);
            roofType();
            totalMaterial(roofT);
        }
    }else{
        printf("\n******* You inputed wrong choice please try again *******\n\n");
        building();
    }

}

/**
*****Foundation, Slabs and walls size*****
*Common code lines in house() and building() functions includes
*/

void slabsAndWalls(int f)
{
    float sf_total = 0;
    int i = 1;
    int j = 1;
    float foundation;
    float slabTotVol = 0;
    float slabTotArea = 0;
    float sbThik = 0;
    int tie;
    float length;
    float cross;

    printf("\n--> How many square feet in structural floor floor(on ground floor) : ");
    scanf("%f", &foundation);
    printf("--> Enter Your number of Tie Beams : ");///total tie beams of foundation
    scanf("%d",&tie);
    printf("--> Enter Your Tie Beam's Length in feet : ");
    scanf("%f",&length);
    float lengthT = length*tie;
    printf("--> How many Cross-sectional area in square feet : ");
    scanf("%f",&cross);
    float volT=length*cross*tie;///total volume of tie beams
    system("cls");
    gfCost(volT, lengthT, foundation);

    if(f > 1)
    {
        while (i < f)
        {
            float sb;

            printf("--> How many square feet in slab of %d floor : ", i);
            scanf("%f", &sb);
            printf("--> How many thickness in a slab : ");
            scanf("%f", &sbThik);

            slabTotArea += sb;
            slabTotVol += sb * sbThik;
            i++;
        }
        system("cls");

        slabsCost(slabTotVol, slabTotArea);

    }
    float totTileCoverage = slabTotArea+foundation;
    tileCost(totTileCoverage);

    ///*****walls in each floor size*****

    printf("--> How many square feet of walls in ground floor : ");

    scanf("%f", &sf_total);

    while (j < f)
    {
        float sf;
        printf("--> How many square feet of walls in %d floor : ", j);
        scanf("%f", &sf);
        sf_total += sf;
        j++;
    }

    system("cls");
    wallsCost(sf_total);
}
/**
*******concrete bars in same floor structure*******
*/
void columnSame(int f)
{
    float area;
    float hight;
    int no_ofBars;
    float totalVol;
    float tHight;

    printf("--> How many cross-sectional area in column(square feet) : ");
    scanf("%f", &area);
    printf("--> How many hight in column(feet) : ");
    scanf("%f", &hight);
    float vol = area * hight;

    int number;
    printf("--> Number of column in a floor : ");
    scanf("%d", &number);
    no_ofBars = f * number;

    tHight = hight * no_ofBars;
    totalVol = vol * no_ofBars;

    system("cls");

    columnsCost(totalVol, tHight);
}

/**
*******concrete bars in different floor structure********
*/
void columnDif(int f)
{
    float area;
    float hight;
    int no_ofBars;
    float totalVol;
    float tHight;

    int i = 1;

    printf("--> How many cross-sectional area in column(square feet) : ");
    scanf("%f", &area);
    printf("--> How many hight in column(feet) : ");
    scanf("%f", &hight);
    printf("--> Number of column in ground floor : ");
    scanf("%d", &no_ofBars);
    float vol = area * hight;

    while (i < f)
    {
        int number;
        printf("--> Number of column in %d floor: ", i);
        scanf("%d", &number);
        no_ofBars += number;
        i++;
    }

    tHight = hight * no_ofBars;
    totalVol = no_ofBars * vol;

    system("cls");

    columnsCost(totalVol, tHight);
}

//stairs

void stairs(int fl)
{
    float tread;
    float raiser;
    float width;
    float sQT;
    float thik;
    int total;

    printf("--> How many length in tread of stairs(feet) : ");
    scanf("%f", &tread);
    printf("--> How many length in raiser of stairs(feet) : ");
    scanf("%f", &raiser);
    printf("--> How many width of stairs(feet) : ");
    scanf("%f", &width);
    printf("--> Total square feet of stairs case in a floor : ");
    scanf("%f", &sQT);
    printf("--> Thickness of stairs case : ");
    scanf("%f", &thik);
    printf("--> Total steps of stairs in floor: ");
    scanf("%d", &total);

    float stepVol = 0.5*tread*raiser*total;//Total steps volume in a floor
    float stepVolT = stepVol*(fl-1);//Total steps volume in building
    float sCasesVol = sQT*thik;//total stairs case volume in a floor
    float sCasesVolT = sCasesVol*(fl-1);//Total stairs volume in a building
    float totConcreteVol = stepVolT+sCasesVolT;//Total concrete volume of stairs
    float totSqftsCase = sQT*(fl-1);//Total square foots of stairs Case in building or house

    system("cls");

    stairsCost(totConcreteVol, totSqftsCase);///stairs cost and material quantity callculation

}
///roof
void roofType()
{

    printf("");


    float roof;
    float thick;

    puts("\t***************************");
    puts("\t*  Select your roof type  *");
    puts("\t*1. If slab roof          *");
    puts("\t*2. else                  *");
    puts("\t***************************");
    printf("\tEnter your choice <1 or 2>: ");
    scanf("%d", &roofT);


    if (roofT == 1 || roofT == 2)
    {
        if (roofT == 2)
        {
            printf("\n--> How many square feet in roof : ");
            scanf("%f", &roof);

            system("cls");

            sheetRoofCost(roof);
        }
        else
        {
            printf("\n--> How many square feet in roof : ");
            scanf("%f", &roof);
            printf("--> How many square feet in roof : ");
            scanf("%f", &thick);
            float roofVol = roof*thick;

            system("cls");

            slabRoofCost(roofVol, roof);
        }
    }else{
        printf("\n******* You inputed wrong choice please try again *******\n\n");
        roofType();
    }

}
/**
*   Cost Calculations
*/
///columns
void columnsCost(double t, double h)
{

    float cement = 11;//11 50Kg bags for one cubic meter
    float sand = 15;//cubic feet for one cubic meter
    float metal = 30;// cubic feet for one cubic meter
    float reinforcementBars = 3.556;//Reinforcement bars 1 meter for Kg
    float bindingWires = reinforcementBars*0.01;//Binding wires meter -1 for Kg

    float vo = t/35.3147;
    float hi = h/3.28084;

    cemenT += cement*vo;
    sandT += (sand*vo)/100;
    metalT += (metal*vo)/100;
    steelsT += (reinforcementBars + bindingWires)*hi;

    float costC_units = cement*cC+sand*(sC/100)+metal*(mC/100);///cost of concrete which needs for 1 cubic meter
    float rCost = (reinforcementBars + bindingWires)*rCk*hi;
    float costTotal = costC_units*vo + rCost;
    totalBill += costTotal;
    printf("\t-----> Total cost of columns : LKR %.2f <-----\n\n", costTotal);
}

///slabs
void slabsCost(double v, double a)
{

    float cement = 11;//11 50Kg bags for one cubic meter
    float sand = 15;//cubic feet for one cubic meter
    float metal = 30;// cubic feet for one cubic meter
    float reinforcementBars = 20.202;//Reinforcement bars square meter -1 for Kg
    float bindingWires = reinforcementBars*0.01; //Binding wires square meter -1 for Kg

    float vo = v/35.3147;
    float sq = a/10.7639;

    cemenT += cement*vo;
    sandT += (sand*vo)/100;
    metalT += (metal*vo)/100;
    steelsT += (reinforcementBars + bindingWires)*sq;

    float costC_units = cement*cC+sand*(sC/100)+metal*(mC/100);///cost of concrete which needs for 1 cubic meter
    float rCost = (reinforcementBars + bindingWires)*rCk*sq;
    float costTotSlab = costC_units*vo + rCost;
    totalBill += costTotSlab;
    printf("\t-----> Total cost of slabs : LKR %.2f <-----\n\n", costTotSlab);
}

///walls
void wallsCost(double sq)
{

    float cement = 30.5821872;//Kg
    float sand = 2.25;//cubic foots
    float firedBriks = 50;
    float paint = 0.13454875;
    float filler = 0.13454875;
    float paint2side = paint*2;
    float filler2side = filler*2;

    float sM = sq/10.7639;

    cemenT += (cement*sM)/50;
    sandT += (sand*sM)/100;
    firedBriksT += 50*sM;
    paintT += paint2side*sM;
    fillerT += filler2side*sM;


    float costForUnit = cement*(cC/50)+sand*(sC/100)+firedBriks*firedBrik+paint2side*(paintC/4)+filler2side*(fillerC/4);
    float costTotWalls = costForUnit*sM;
    totalBill += costTotWalls;
    printf("\t-----> Total cost of walls : LKR %.2f <-----\n\n", costTotWalls);
}

///
void stairsCost(double tV, double tA)
{
    float cement = 11;//11 50Kg bags for one cubic meter
    float sand = 15;//cubic feet for one cubic meter
    float metal = 30;// cubic feet for one cubic meter
    float reinforcementBars = 20.202;//Reinforcement bars square meter -1 for Kg
    float bindingWires = reinforcementBars*0.01; //Binding wires square meter -1 for Kg

    float vo = tV/35.3147;
    float sq = tA/10.7639;

    cemenT += cement*vo;///total cement bags for strairs. this quantity adding total quantity
    sandT += (sand*vo)/100;///total sand cube for strairs. this quantity adding total quantity
    metalT += (metal*vo)/100;///total metal cube for strairs. this quantity adding total quantity
    steelsT += (reinforcementBars + bindingWires)*sq;///total steel for strairs. this quantity adding total quantity

    float costC_units = cement*cC+sand*(sC/100)+metal*(mC/100);///cost of concrete which needs for 1 cubic meter
    float rCost = (reinforcementBars + bindingWires)*rCk*sq;///total steel cost
    float costTotStrairs = costC_units*vo + rCost;///total strairs cost
    totalBill += costTotStrairs;
    printf("\t-----> Total cost of strairs : LKR %.2f <-----\n\n", costTotStrairs);
}

///Slab roof cost
void slabRoofCost(double voL, double sqU)
{
    float cement = 11;//11 50Kg bags for one cubic meter
    float sand = 15;//cubic feet for one cubic meter
    float metal = 30;// cubic feet for one cubic meter
    float reinforcementBars = 20.202;//Reinforcement bars square meter -1 for Kg
    float bindingWires = reinforcementBars*0.01; //Binding wires square meter -1 for Kg

    float vo = voL/35.3147;
    float sq = sqU/10.7639;

    cemenT += cement*vo;
    sandT += (sand*vo)/100;
    metalT += (metal*vo)/100;
    steelsT += (reinforcementBars + bindingWires)*sq;

    float costC_units = cement*cC+sand*(sC/100)+metal*(mC/100);///cost of concrete which needs for 1 cubic meter
    float rCost = (reinforcementBars + bindingWires)*rCk*sq;
    float costTotRoof = costC_units*vo + rCost;
    totalBill += costTotRoof;
    printf("\n\t-----> Total cost of Roof : LKR %.2f <-----\n\n", costTotRoof);
}

void tileCost(float a)
{
    float tileMc_for_sqft = tileMc/100;/// Tile mortar cost for one Sq.ft
    float tileC_for_sqft = tileC/4;/// Tile cost for one Sq.ft
    float totFloor = a;///Total floor Sq.ft

    tilesT = totFloor/4;///total 2x2 tiles
    tileMT = totFloor/100;///total 20Kg tile mortar bags
    float totTileCost = totFloor*tileC_for_sqft+totFloor*tileMc_for_sqft;
    totalBill += totTileCost;
    printf("\n\t-----> Total cost of Tile : LKR %.2f <-----\n\n", totTileCost);

}
///Sheets Roof
void sheetRoofCost(double sQ)
{
    sheetsT = sQ/35.12;
    float steel = sQ*1;

    steelsT += steel;

    float costTotRoof = sheetsT*sheetC+steel*rCk;
    totalBill += costTotRoof;
    printf("\t-----> Total cost of Roof : LKR %.2f <-----\n\n", costTotRoof);
}

///ground floor cost(foundation(tie beams) and tile bed)
void gfCost(double vOl,double len, double sqq)
{
    ///tie beam materials
    float cement = 11;//11 50Kg bags for one cubic meter tie beam
    float sand = 15;//cubic feet for one cubic meter
    float metal = 30;// cubic feet for one cubic meter
    float reinforcementBars = 3.556;//Reinforcement bars 1 meter for Kg
    float bindingWires = reinforcementBars*0.01;//Binding wires meter -1 for Kg

    ///tile bed materials in all floor
    float sqm = sqq/10.7639;///convert ground floor area square feet to square meter
    float cement2 =5.5*sqm;///cement quantity for ground floor tile bed in Kg
    float sand2 = 0.72*sqm;///sand quantity ground floor tile bed cubic feet

    cemenT += cement2/50;///total cement bags for tile bed in ground floor. this quantity adding total quantity
    sandT += sand2/100;///total sand cubes for tile bed in ground floor. this quantity adding total quantity

    float tileBedCost = cement2*(cC/50)+sand2*(sC/100);///tile bed cost

    float vo = vOl/35.3147;///convert to cubic meter
    float leng = len/3.28084;///convert to meter

    cemenT += cement*vo;
    sandT += (sand*vo)/100;
    metalT += (metal*vo)/100;
    steelsT += (reinforcementBars + bindingWires)*leng;

    float costC_units = cement*cC+sand*(sC/100)+metal*(mC/100);///cost of concrete which needs for 1 cubic meter
    float rCost = (reinforcementBars + bindingWires)*rCk*leng;///steel cost for tie beams
    float gfcostTotal = costC_units*vo + rCost+tileBedCost;///total cost
    totalBill += gfcostTotal;

    printf("\t-----> Total cost of structural floor(on ground floor) : LKR %.2f <-----\n\n", gfcostTotal);
}

void totalMaterial(int rT)
{
    struct materialList{char material[20]; float quantity; char unit[10]; float price;};

    struct materialList m1 = {"Cement",cemenT,"50Kg bags",cemenT*cC};
    struct materialList m2 = {"Sand",sandT,"Cubes",sandT*sC};
    struct materialList m3 = {"Metal",metalT,"Cubes",metalT*mC};
    struct materialList m4 = {"Steel",steelsT/100,"ton",(steelsT/1000)*rCt};
    struct materialList m5 = {"Fired Bricks",firedBriksT,"NOS",firedBriksT*firedBrik};
    struct materialList m6 = {"Paint",paintT,"L",paintT*(paintC/4)};
    struct materialList m7 = {"Filler",fillerT,"L",fillerT*(fillerC/4)};
    struct materialList m8 = {"Tiles(2x2)",tilesT,"NOS",tilesT*tileC};
    struct materialList m9 = {"Tile mortar",tileMT,"20Kg bags",tileMT*tileMc};
    if(rT == 2);
    struct materialList m10 = {"Sheets",sheetsT,"NOS",sheetsT*sheetC};

    FILE *fp;
    fp = fopen("Bill of Quantity.txt" , "w");


    puts("\t\t\t****************************");
    puts("\t\t\t*     Bill of Quantity     *");
    puts("\t\t\t****************************");


    printf("\n-->\tMaterial\tQuantity\tUnits\t\tPrice(LKR)\n\n");

    printf("\n-->\t%s\t\t%.0f\t\t%s\t%.2f\n",  m1.material, m1.quantity, m1.unit, m1.price);
    printf("\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m2.material, m2.quantity, m2.unit, m2.price);
    printf("\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m3.material, m3.quantity, m3.unit, m3.price);
    printf("\n-->\t%s\t\t%.2f\t\t%s\t\t%.2f\n",  m4.material, m4.quantity, m4.unit, m4.price);
    printf("\n-->\t%s\t%.0f\t\t%s\t\t%.2f\n",  m5.material, m5.quantity, m5.unit, m5.price);
    printf("\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m6.material, m6.quantity, m6.unit, m6.price);
    printf("\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m7.material, m7.quantity, m7.unit, m7.price);
    printf("\n-->\t%s\t%.0f\t\t%s\t\t%.2f\n",  m8.material, m8.quantity, m8.unit, m8.price);
    printf("\n-->\t%s\t%.0f\t\t%s\t%.2f\n",  m9.material, m9.quantity, m9.unit, m9.price);
    if(rT == 2)
    printf("\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m10.material, m10.quantity, m10.unit, m10.price);


    printf("\n\t\t\t\t\tTotal Bill\t%0.2f\n\n", totalBill);

    puts("\t*************************************************************");
    puts("\t*                         Our Team                          *");
    puts("\t*                                                           *");
    puts("\t*     Y. E. Y Amarasekara - UWU/CST/20/073                  *");
    puts("\t*     D. S. M. D. N. B. Samarakoon - UWU/CST/20/018         *");
    puts("\t*     W. M. S. Gunawardhana  - UWU/CST/20/081               *");
    puts("\t*     R. M.Sewmini Dulanji Rathnayaka  - UWU/CST/20/055     *");
    puts("\t*     H. P. N. S. Weerakoon  - UWU/CST/20/036               *");
    puts("\t*                                                           *");
    puts("\t*************************************************************");

    fprintf(fp , "%s", "\t\t\t****************************\n");
    fprintf(fp , "%s", "\t\t\t*     Bill of Quantity     *\n");
    fprintf(fp , "%s", "\t\t\t****************************\n");

    fprintf(fp,"\n-->\tMaterial\tQuantity\tUnits\t\tPrice(LKR)\n\n");

    fprintf(fp,"\n-->\t%s\t\t%.0f\t\t%s\t%.2f\n",  m1.material, m1.quantity, m1.unit, m1.price);
    fprintf(fp,"\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m2.material, m2.quantity, m2.unit, m2.price);
    fprintf(fp,"\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m3.material, m3.quantity, m3.unit, m3.price);
    fprintf(fp,"\n-->\t%s\t\t%.2f\t\t%s\t\t%.2f\n",  m4.material, m4.quantity, m4.unit, m4.price);
    fprintf(fp,"\n-->\t%s\t%.0f\t\t%s\t\t%.2f\n",  m5.material, m5.quantity, m5.unit, m5.price);
    fprintf(fp,"\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m6.material, m6.quantity, m6.unit, m6.price);
    fprintf(fp,"\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m7.material, m7.quantity, m7.unit, m7.price);
    fprintf(fp,"\n-->\t%s\t%.0f\t\t%s\t\t%.2f\n",  m8.material, m8.quantity, m8.unit, m8.price);
    fprintf(fp,"\n-->\t%s\t%.0f\t\t%s\t%.2f\n",  m9.material, m9.quantity, m9.unit, m9.price);
    if(rT == 2)
    fprintf(fp,"\n-->\t%s\t\t%.0f\t\t%s\t\t%.2f\n",  m10.material, m10.quantity, m10.unit, m10.price);

    fprintf(fp,"\n\t\t\t\t\tTotal Bill\t%0.2f\n\n\n", totalBill);

    fprintf(fp , "%s", "\t*************************************************************\n");
    fprintf(fp , "%s", "\t*                         Our Team                          *\n");
    fprintf(fp , "%s", "\t*                                                           *\n");
    fprintf(fp , "%s", "\t*     Y. E. Y Amarasekara - UWU/CST/20/073                  *\n");
    fprintf(fp , "%s", "\t*     D. S. M. D. N. B. Samarakoon - UWU/CST/20/018         *\n");
    fprintf(fp , "%s", "\t*     W. M. S. Gunawardhana  - UWU/CST/20/081               *\n");
    fprintf(fp , "%s", "\t*     R. M.Sewmini Dulanji Rathnayaka  - UWU/CST/20/055     *\n");
    fprintf(fp , "%s", "\t*     H. P. N. S. Weerakoon  - UWU/CST/20/036               *\n");
    fprintf(fp , "%s", "\t*                                                           *\n");
    fprintf(fp , "%s", "\t*************************************************************\n");

    fclose(fp);
}
