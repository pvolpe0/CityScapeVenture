# CityScapeVenture

Members:
Seth Horowitz
Aram Sarafian
Pablo Volpe

Overall Idea:
Allow a user to move around a procedurally generated city. 
Movement will be google maps style, using wasd


Technical features with requirements:

Procedurally generated city - 
Must include 3 types of buildings, a park (a flat rectangular piece of land is fine), and roads that are more complex than a regular square grid (even Manhattan is more complex than a grid!)
Creativity points if you can input an actual city's data for the roads! 

Procedurally modeled buildings - 
Must have 3 non-identical portions (top, middle, bottom OR 1st floor, 2nd floor, roof).
Generate at least 3 different buildings with differently shaped windows. 

Shape grammar buildings - 
At least 5 different shapes must be used, and there must be rules for how they can be combined. It is not acceptable to allow their combination in completely arbitrary ways. 

Procedurally generated plants with L-sytems - 
At least 4 language variables (X, F, +, -), and parameters (length of F, theta of + and -).
To make it 3D you can also add another axis for rotation(typical variables are & and ^).
At least 3 trees that demonstrate different rules.
Pseudorandom execution will make your trees look more varied and pretty. 


Technical strategies:
Use c++ rand() function with seed based on world space coordinates

Procedurally generated city -
Set up grid around player with each point on grid representing an intersection
Apply function to displace intersections based on world coordinates
Build roads based on displaced coordinates

Prodedurally generated shape grammar buildings - 
Use world space coordinates to get sequence of shape grammar operations
Use block position for some operations to make buildings on a block similiar

Procedurally generated plants - 
Use L-systems
No idea how to do this