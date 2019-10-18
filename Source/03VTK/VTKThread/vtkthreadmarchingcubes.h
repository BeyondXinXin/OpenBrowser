/*
 * vtk线程  MarchingCubes 2维转3维
*/

#ifndef VTKTHREADMARCHINGCUBES_H
#define VTKTHREADMARCHINGCUBES_H

//05vtkthred
#include "vtkthread.h"

//vtk
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkAlgorithmOutput.h>




class VtkThreadMarchingCubes: public VtkThread {
    Q_OBJECT

  public:
    explicit VtkThreadMarchingCubes(QObject *parent = nullptr);
    virtual ~VtkThreadMarchingCubes() override;
    void SetInputImageData(const vtkSmartPointer<vtkImageData>value);
    void Setnum(int num);
    vtkSmartPointer<vtkMarchingCubes> Getmarchingcubes() ;
    int marchcubes_num_;



  protected:
    virtual void run() override;
  private:
    void Initial();
    void Execute();
  private:
    vtkNew< vtkMarchingCubes > marchcubes_ ;

    vtkSmartPointer<vtkImageData> imagedata_;
};

#endif // VTKTHREADMARCHINGCUBES_H
