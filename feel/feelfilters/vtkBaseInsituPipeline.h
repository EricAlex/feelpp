
#ifndef FEELPP_VTKBASEINSITUPIPELINE_HPP
#define FEELPP_VTKBASEINSITUPIPELINE_HPP 1

#include <string>
#include <map>

#include <feel/feelcore/environment.hpp>

#include <vtkStdString.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkObjectFactory.h>

#include <vtkSMProxy.h>
#include <vtkSMSourceProxy.h>
#include <vtkSMProxyManager.h>
#include <vtkSMSessionProxyManager.h>
#include <vtkCPDataDescription.h>
#include <vtkCPInputDataDescription.h>
#include <vtkCPPipeline.h>
#include <vtkPVTrivialProducer.h>
#include <vtkLiveInsituLink.h>

namespace Feel
{

class vtkBaseInsituPipeline : public vtkCPPipeline
{
    public:
        static vtkBaseInsituPipeline* New();
        vtkTypeMacro(vtkBaseInsituPipeline,vtkCPPipeline);
        virtual void PrintSelf(ostream& os, vtkIndent indent);
        virtual void Initialize();

        virtual int RequestDataDescription(vtkCPDataDescription* dataDescription);
        virtual int CoProcess(vtkCPDataDescription* dataDescription);
    protected:
        vtkBaseInsituPipeline();
        virtual ~vtkBaseInsituPipeline();
    private:
        void CreatePipeline(vtkCPDataDescription* dataDescription, std::string inname);
        void UpdateProducers(vtkCPDataDescription* dataDescription);
        void DoLiveVisualization(vtkCPDataDescription* dataDescription);

        vtkBaseInsituPipeline(const vtkBaseInsituPipeline&); // Not implemented
        void operator=(const vtkBaseInsituPipeline&); // Not implemented
        int OutputFrequency;
        std::string FileName;

        bool pipelineCreated;

        vtkSMProxyManager* M_pxm;
        vtkSMSessionProxyManager* M_spxm;

        std::map<std::string, vtkSmartPointer<vtkSMSourceProxy>> M_producerMap;
        //std::map<std::string, vtkSmartPointer<vtkSMSourceProxy>> M_producerMap;

        vtkSmartPointer<vtkLiveInsituLink> M_insituLink;
        vtkSmartPointer<vtkSMProxy> M_proxy;
};

}
#endif