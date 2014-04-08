/*=========================================================================

Program: FEMUS
Module: MultiLevelProblem
Authors: Eugenio Aulisa, Simone Bnà
 
Copyright (c) FEMTTU
All rights reserved. 

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __MultiLevelSolution_hpp__
#define __MultiLevelSolution_hpp__

//----------------------------------------------------------------------------
// includes :
//----------------------------------------------------------------------------
#include "MultiLevelMesh.hpp"
#include "Solution.hpp"
#include "ParallelObject.hpp"

#include <vector>

typedef double (*initfunc) (const double &x, const double &y, const double &z);

/**
 * This class is a black box container to handle multilevel solutions.
 */

class MultiLevelSolution : public ParallelObject {

private:
  bool _bdc_func_set;
  bool _init_func_set;
  

 
    
private:
  
  unsigned short  _gridn;
 
  vector <char*>  _SolName;
  vector <int>    _SolType;
  vector <char*>  _BdcType;
  vector <int>    _SolTmorder;
  vector <bool>   _TestIfPressure;
  vector <bool>   _TestIfDisplacement;
  

public:
 
  /** Array of solution */
  vector <Solution*>  _solution;
  
  /** Multilevel mesh */
  MultiLevelMesh* _ml_msh;
  
  /** Constructor */
  MultiLevelSolution( MultiLevelMesh *ml_msh);

  /** Destructor */
  ~MultiLevelSolution();
     
  // Vector handling functions
  void AddSolution(const char name[], const char type[],unsigned tmorder=0, const bool &Pde_type=1);
  void AssociatePropertyToSolution(const char solution_name[], const char solution_property[]);
  void ResizeSolutionVector( const char name[]);
  void Initialize(const char name[], initfunc func = NULL);
  unsigned GetIndex(const char name[]) const;
  unsigned GetSolType(const char name[]);
  void BuildProlongatorMatrix(unsigned gridf, unsigned SolIndex);
  
  
  // boundary condition function pointer
  bool (*_SetBoundaryConditionFunction) (const double &x, const double &y, const double &z,const char name[], 
                                         double &value, const int FaceName, const double time);
  
  void AttachSetBoundaryConditionFunction ( bool (* SetBoundaryConditionFunction) (const double &x, const double &y, const double &z,const char name[], 
										   double &value, const int FaceName, const double time) );
  
  void GenerateBdc(const char name[], const char bdc_type[]="Steady");
  void UpdateBdc(const double time);
  void GenerateBdc(const unsigned int k, const double time);
  
  
  char* GetSolutionName(unsigned i){return _SolName[i];};
  int   GetSolutionType(unsigned i){return _SolType[i];};
  char* GetBdcType(unsigned i){return _BdcType[i];};
  int   GetSolutionTimeOrder(unsigned i){return _SolTmorder[i];};
  bool  TestIfSolutionIsPressureType(unsigned i){return _TestIfPressure[i];};
  bool  TestIfSolutionIsDisplacemenetType(unsigned i){return _TestIfDisplacement[i];};
  
};

#endif
