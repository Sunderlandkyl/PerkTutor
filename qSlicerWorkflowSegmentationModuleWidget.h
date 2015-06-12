
#ifndef __qSlicerWorkflowSegmentationModuleWidget_h
#define __qSlicerWorkflowSegmentationModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"
#include <QtGui>
#include "qSlicerWorkflowSegmentationModuleExport.h"

#include "qSlicerMessagesWidget.h"
#include "qSlicerTransformBufferWidget.h"
#include "qSlicerWorkflowSegmentationRecorderControlsWidget.h"

class qSlicerWorkflowSegmentationModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLWorkflowSegmentationNode;


/// \ingroup Slicer_QtModules_WorkflowSegmentation
class Q_SLICER_QTMODULES_WORKFLOWSEGMENTATION_EXPORT qSlicerWorkflowSegmentationModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerWorkflowSegmentationModuleWidget(QWidget *parent=0);
  virtual ~qSlicerWorkflowSegmentationModuleWidget();

protected:
  QScopedPointer<qSlicerWorkflowSegmentationModuleWidgetPrivate> d_ptr;
  
  virtual void setup();
  virtual void setupEmbeddedWidgets();


protected slots:

  void mrmlNodeChanged();
  
  void updateWidgetFromMRMLNode();

private:
  Q_DECLARE_PRIVATE(qSlicerWorkflowSegmentationModuleWidget);
  Q_DISABLE_COPY(qSlicerWorkflowSegmentationModuleWidget);

  QLabel* InstructionLabel;
};

#endif
