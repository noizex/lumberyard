/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include <AzCore/std/containers/vector.h>
#include <EMotionFX/Source/AnimGraphNode.h>
#include <EMotionFX/Source/EMotionFXConfig.h>
#include <EMotionFX/Source/ObjectAffectedByParameterChanges.h>


namespace EMotionFX
{
    /**
     *
     *
     */
    class EMFX_API BlendTreeParameterNode
        : public AnimGraphNode
        , public ObjectAffectedByParameterChanges
    {
    public:
        AZ_RTTI(BlendTreeParameterNode, "{4510529A-323F-40F6-B773-9FA8FC4DE53D}", AnimGraphNode, ObjectAffectedByParameterChanges)
        AZ_CLASS_ALLOCATOR_DECL

        BlendTreeParameterNode();
        ~BlendTreeParameterNode() override;

        void Reinit() override;
        bool InitAfterLoading(AnimGraph* animGraph) override;
        
        AZ::Color GetVisualColor() const override;

        const char* GetPaletteName() const override;
        AnimGraphObject::ECategory GetPaletteCategory() const override;

        const AZStd::vector<AZ::u32>& GetParameterIndices() const;
        uint32 GetParameterIndex(uint32 portNr) const;

        /// Add a parameter to the parameter mask and also add a port for it.
        void AddParameter(const AZStd::string& parameterName);

        /// Set the parameter mask and create ports for each of them. (An empty parameter list means that all parameters are shown).
        void SetParameters(const AZStd::string& parameterNamesWithSemicolons);
        void SetParameters(const AZStd::vector<AZStd::string>& parameterNames);

        /// Construct a string containing all parameter names separated by semicolons.
        AZStd::string ConstructParameterNamesString() const;
        static AZStd::string ConstructParameterNamesString(const AZStd::vector<AZStd::string>& parameterNames);
        static AZStd::string ConstructParameterNamesString(const AZStd::vector<AZStd::string>& parameterNames, const AZStd::vector<AZStd::string>& excludedParameterNames);

        /// Remove the given parameter by name. This removes the parameter from the parameter mask and also deletes the port.
        void RemoveParameterByName(const AZStd::string& parameterName);

        /// Sort the parameter names based on the order of the parameters in the anim graph.
        static void SortParameterNames(AnimGraph* animGraph, AZStd::vector<AZStd::string>& outParameterNames);

        static void Reflect(AZ::ReflectContext* context);

        // ParameterDrivenPorts
        AZStd::vector<AZStd::string> GetParameters() const override;
        AnimGraph* GetParameterAnimGraph() const override;
        void ParameterMaskChanged(const AZStd::vector<AZStd::string>& newParameterMask) override;
        void AddRequiredParameters(AZStd::vector<AZStd::string>& parameterNames) const override;
        void ParameterAdded(size_t newParameterIndex) override;
        void ParameterRenamed(const AZStd::string& oldParameterName, const AZStd::string& newParameterName) override;
        void ParameterOrderChanged(const ValueParameterVector& beforeChange, const ValueParameterVector& afterChange) override;
        void ParameterRemoved(const AZStd::string& oldParameterName) override;

    private:
        bool GetTypeSupportsFloat(uint32 parameterType);

        AZStd::vector<AZStd::string>    m_parameterNames;
        AZStd::vector<AZ::u32>          m_parameterIndices;              /**< The indices of the visible and available parameters. */

        void Update(AnimGraphInstance* animGraphInstance, float timePassedInSeconds) override;
    };
} // namespace EMotionFX