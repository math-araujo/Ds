//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2022, 2023 Paulo Pagliosa.                        |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: CameraProxy.cpp
// ========
// Source file for camera proxy.
//
// Author: Paulo Pagliosa
// Last revision: 22/01/2022

#include "graph/CameraProxy.h"
#include "graph/Transform.h"
#include "graph/SceneObject.h"
#include <cassert>

namespace cg::graph
{ // begin namespace cg::graph

  /////////////////////////////////////////////////////////////////////
  //
  // CameraProxy implementation
  // ===========
  Camera *CameraProxy::_current;

  CameraProxy::~CameraProxy()
  {
    if (camera() == _current)
      _current = nullptr;
  }

  void
  CameraProxy::transformChanged()
  {
    auto t = transform();

    assert(t->changed());
    _object->setTransform(t->position(), t->rotation());
  }

  void
  CameraProxy::reset(float aspect)
  {
    _object->setDefaultView(aspect);
  }

  void
  CameraProxy::setCurrent(Camera *camera)
  {
    if (camera != _current)
      _current = camera;
  }

} // end namespace cg::graph
