/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkMRMLWorkflowSegmentationNode.h,v $
  Date:      $Date: 2006/03/19 17:12:28 $
  Version:   $Revision: 1.6 $

=========================================================================auto=*/

#ifndef __vtkMRMLWorkflowSegmentationNode_h
#define __vtkMRMLWorkflowSegmentationNode_h

#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

#include "vtkMRMLModelNode.h"
#include "vtkTransform.h"
#include "vtkMRMLNode.h"
#include "vtkMRML.h"
#include "vtkMRMLScene.h"

// WorkflowSegmentation includes
#include "vtkSlicerWorkflowSegmentationModuleMRMLExport.h"

class vtkActor;
class vtkImageActor;
class vtkMatrix4x4;
class vtkPolyData;
class vtkRenderer;
class vtkTransform;


class vtkImageData;
class vtkMRMLLinearTransformNode;
class vtkMRMLModelNode;
class vtkMRMLViewNode;
class vtkMRMLVolumeNode;



//-------------------------------------------------------------------------
// Helper classes for MRML
//-------------------------------------------------------------------------

// Class to store observed transforms
class TransformRecord
{
public:
  std::string DeviceName;
  std::string Transform;
  long int TimeStampSec; 
  int TimeStampNSec;     // Nanoseconds from TimeStampSec to the real timestamp.
  std::string Task;
};

// Class to store recorded messages
class MessageRecord
{
public:
  std::string Message;
  long int TimeStampSec;
  int TimeStampNSec;
};

// Class to store algorithm input parameters
class InputParameter
{
public:
  int NumTasks;
  double FilterWidth;
  int OrthogonalOrder;
  int OrthogonalWindow;
  int Derivative;
  int NumCentroids;
  int NumPrinComps;
  double MarkovPseudoScalePi, MarkovPseudoScaleA, MarkovPseudoScaleB;
};

// Class to store algorithm training parameters
class TrainingParameter
{
public:
  std::string PrinComps;
  std::string Centroids;
  std::string MarkovPi;
  std::string MarkovA;
  std::string MarkovB;
};






//-------------------------------------------------------------------------
// MRML Node classes
//-------------------------------------------------------------------------


class
VTK_SLICER_WORKFLOWSEGMENTATION_MODULE_MRML_EXPORT
vtkMRMLWorkflowSegmentationNode
: public vtkMRMLNode
{
public:
  
  //Enumeration of events
  //BTX
  enum {
    TransformChangedEvent = 201001,
    RecordingStartEvent   = 200901,
    RecordingStopEvent    = 200902
  };
  //ETX
  
  // Standard MRML node methods  
  static vtkMRMLWorkflowSegmentationNode *New();
  vtkTypeMacro( vtkMRMLWorkflowSegmentationNode, vtkMRMLNode );
  virtual vtkMRMLNode* CreateNodeInstance();
  virtual const char* GetNodeTagName() { return "WorkflowSegmentation"; };
  void PrintSelf( ostream& os, vtkIndent indent );
  virtual void ReadXMLAttributes( const char** atts );
  virtual void WriteXML( ostream& of, int indent );
  virtual void Copy( vtkMRMLNode *node );
  virtual void UpdateScene( vtkMRMLScene * );
  void ProcessMRMLEvents ( vtkObject *caller, unsigned long event, void *callData );
  
  
  virtual void UpdateReferenceID( const char *oldID, const char *newID );
  void UpdateReferences();
  void StartReceiveServer();
  void StopReceiveServer();
  
  
protected:

  // Constructor/desctructor methods
  vtkMRMLWorkflowSegmentationNode();
  virtual ~vtkMRMLWorkflowSegmentationNode();
  vtkMRMLWorkflowSegmentationNode ( const vtkMRMLWorkflowSegmentationNode& );
  void operator=( const vtkMRMLWorkflowSegmentationNode& );

  void RemoveMRMLObservers();
    
  
public:
  
  // Reference to observed transform nodes.
  void AddObservedTransformNode( const char* TransformNodeID );
  void RemoveObservedTransformNode( const char* TransformNodeID );
  void ClearObservedTranformNodes();
  vtkMRMLLinearTransformNode* GetObservedTransformNode( const char* TransformNodeID );

protected:

  // Reference to observed transform nodes
  std::vector< char* > ObservedTransformNodeIDs;
  std::vector< vtkMRMLLinearTransformNode* > ObservedTransformNodes;
  
  
public:

  // Statistics associated with recorded transforms
  unsigned int GetTransformsBufferSize();
  unsigned int GetMessagesBufferSize();
  double GetTotalTime();
  std::string GetCurrentTask();
  std::string GetCurrentInstruction();
  std::string GetNextTask();
  std::string GetNextInstruction();
  
  vtkGetMacro( Recording, bool );
  void SetRecording( bool newState );
  
  // Setters for saving the scene
  //BTX
  void SetTransformSelections( std::vector< int > selections );
  void SetLogFileName( std::string fileName );
  void SaveIntoFile( std::string fileName );
  std::string GetLogFileName();
  void CustomMessage( std::string message, int sec = -1, int nsec = -1 );
  //ETX
  
  // File IO methods
  void UpdateFileFromBuffer();
  void ImportTrainingData( std::string dirName );
  void ImportInputParameters( std::string fileName );
  //void TrainSegmentationAlgorithm();
  void ClearBuffer();
  
  // Get the current time stamp sec, nanosec
  void GetTimestamp( int &sec, int &nsec );
  
  
protected:
  
  //Observe a new transform
  void AddNewTransform( const char* TransformNodeID ); 
  
  // Variables associated with recording
  //BTX
  std::vector< int > TransformSelections;  
  std::string LogFileName;
  std::string InputParameterFileName;
  std::string TrainingParameterFileName;
  std::vector< TransformRecord > TransformsBuffer;
  std::vector< MessageRecord > MessagesBuffer;
  //ETX
 
  // Active recording
  bool Recording;
  bool Active;
  
  // Time.
  // Set a zero timestamp in the constructor using the system clock.  
  clock_t Clock0;
  
  // Clock synchronization
  double IGTLTimeOffsetSeconds;  // Adding this to the IGTL timestamp synchronizes it with the clock.
  bool IGTLTimeSynchronized;

  // Keep track of the last recorded transform to avoid repeats
  vtkTransform* LastNeedleTransform;
  double LastNeedleTime;

public:
  // Parameter variables
  InputParameter inputParam;
  TrainingParameter trainingParam;
  
};  

#endif
