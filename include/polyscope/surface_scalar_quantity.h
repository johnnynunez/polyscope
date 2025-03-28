// Copyright 2017-2023, Nicholas Sharp and the Polyscope contributors. https://polyscope.run

#pragma once

#include "polyscope/polyscope.h"

#include "polyscope/affine_remapper.h"
#include "polyscope/histogram.h"
#include "polyscope/render/color_maps.h"
#include "polyscope/render/engine.h"
#include "polyscope/scalar_quantity.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/texture_map_quantity.h"

namespace polyscope {

// forward declarations
class SurfaceMeshQuantity;
class SurfaceMesh;
class SurfaceParameterizationQuantity;

class SurfaceScalarQuantity : public SurfaceMeshQuantity, public ScalarQuantity<SurfaceScalarQuantity> {
public:
  SurfaceScalarQuantity(std::string name, SurfaceMesh& mesh_, std::string definedOn, const std::vector<float>& values_,
                        DataType dataType);

  virtual void draw() override;
  virtual void buildCustomUI() override;
  virtual void buildSurfaceScalarOptionsUI() {};
  virtual std::string niceName() override;
  virtual void refresh() override;

  virtual std::shared_ptr<render::AttributeBuffer> getAttributeBuffer() = 0;

  const std::string definedOn;

protected:
  std::shared_ptr<render::ShaderProgram> program;

  // Helpers
  virtual void createProgram() = 0;
};

// ========================================================
// ==========           Vertex Scalar            ==========
// ========================================================

class SurfaceVertexScalarQuantity : public SurfaceScalarQuantity {
public:
  SurfaceVertexScalarQuantity(std::string name, const std::vector<float>& values_, SurfaceMesh& mesh_,
                              DataType dataType_ = DataType::STANDARD);

  virtual void createProgram() override;

  virtual std::shared_ptr<render::AttributeBuffer> getAttributeBuffer() override;

  void buildVertexInfoGUI(size_t vInd) override;
};


// ========================================================
// ==========            Face Scalar             ==========
// ========================================================

class SurfaceFaceScalarQuantity : public SurfaceScalarQuantity {
public:
  SurfaceFaceScalarQuantity(std::string name, const std::vector<float>& values_, SurfaceMesh& mesh_,
                            DataType dataType_ = DataType::STANDARD);

  virtual void createProgram() override;
  virtual std::shared_ptr<render::AttributeBuffer> getAttributeBuffer() override;
  void buildFaceInfoGUI(size_t fInd) override;
};


// ========================================================
// ==========            Edge Scalar             ==========
// ========================================================

class SurfaceEdgeScalarQuantity : public SurfaceScalarQuantity {
public:
  SurfaceEdgeScalarQuantity(std::string name, const std::vector<float>& values_, SurfaceMesh& mesh_,
                            DataType dataType_ = DataType::STANDARD);

  virtual void createProgram() override;
  virtual std::shared_ptr<render::AttributeBuffer> getAttributeBuffer() override;
  void buildEdgeInfoGUI(size_t edgeInd) override;
};

// ========================================================
// ==========          Halfedge Scalar           ==========
// ========================================================

class SurfaceHalfedgeScalarQuantity : public SurfaceScalarQuantity {
public:
  SurfaceHalfedgeScalarQuantity(std::string name, const std::vector<float>& values_, SurfaceMesh& mesh_,
                                DataType dataType_ = DataType::STANDARD);

  virtual void createProgram() override;
  virtual std::shared_ptr<render::AttributeBuffer> getAttributeBuffer() override;
  void buildHalfedgeInfoGUI(size_t heInd) override;
};

// ========================================================
// ==========          Corner Scalar             ==========
// ========================================================

class SurfaceCornerScalarQuantity : public SurfaceScalarQuantity {
public:
  SurfaceCornerScalarQuantity(std::string name, const std::vector<float>& values_, SurfaceMesh& mesh_,
                              DataType dataType_ = DataType::STANDARD);

  virtual void createProgram() override;
  virtual std::shared_ptr<render::AttributeBuffer> getAttributeBuffer() override;
  void buildCornerInfoGUI(size_t heInd) override;
};

// ========================================================
// ==========          Texture Scalar            ==========
// ========================================================

class SurfaceTextureScalarQuantity : public SurfaceScalarQuantity,
                                     public TextureMapQuantity<SurfaceTextureScalarQuantity> {
public:
  SurfaceTextureScalarQuantity(std::string name, SurfaceMesh& mesh_, SurfaceParameterizationQuantity& param_,
                               size_t dimX, size_t dimY, const std::vector<float>& values_, ImageOrigin origin_,
                               DataType dataType_ = DataType::STANDARD);

  virtual void createProgram() override;
  virtual void buildSurfaceScalarOptionsUI() override;
  virtual std::shared_ptr<render::AttributeBuffer> getAttributeBuffer() override;


protected:
  SurfaceParameterizationQuantity& param;
};

} // namespace polyscope
