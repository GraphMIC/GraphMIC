#pragma once

#include "gmCoreExport.hpp"

#include "gmDataImage.hpp"

#include <mitkImageCast.h>
#include <mitkImageToItk.h>

#include <mitkOpenCVToMitkImageFilter.h>
#include <mitkImageToOpenCVImageFilter.h>

namespace gm
{
    namespace Image
    {
        template <class RItkImageType>
        auto ToItk(Data::Image* image) -> typename RItkImageType::Pointer
        {
            if (!image)
            {
                return nullptr;
            }

            typename mitk::ImageToItk<RItkImageType>::Pointer filter = mitk::ImageToItk<RItkImageType>::New();
            filter->SetInput(image->getMitkImage()->Clone());
            filter->Update();
            
            return filter->GetOutput();
        }
        
        template <class TItkImageType>
        auto FromItk(typename TItkImageType::Pointer image) -> Data::Image*
        {
            mitk::Image::Pointer mitkImageData = mitk::Image::New();
            mitk::CastToMitkImage(image, mitkImageData);
            
            return new Data::Image(mitkImageData);
        }

        GM_CORE_EXPORT auto ToCv(Data::Image* image) -> cv::Mat;

        GM_CORE_EXPORT auto FromCv(cv::Mat cvMat) -> Data::Image*;
    }
}
