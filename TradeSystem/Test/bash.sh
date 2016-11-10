g++ -c tinyxmlparser.cpp -DTIXML_USE_STL
g++ -c tinyxmlerror.cpp -DTIXML_USE_STL
g++ -c tinystr.cpp -DTIXML_USE_STL
g++ -c tinyxml.cpp -DTIXML_USE_STL                                          
g++ -c main.cpp -DTIXML_USE_STL
g++ -o main main.o tinyxmlparser.o tinyxmlerror.o tinystr.o tinyxml.o 
