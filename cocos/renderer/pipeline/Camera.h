#pragma once

namespace cc {
namespace scene {

struct CC_DLL Camera {
    bool isWindowSize = true;
    float screenScale = 0;
    uint clearStencil= 0;
    float clearDepth = 1.0f;
    gfx::ClearFlags clearFlag = gfx::ClearFlags::NONE;
    gfx::Rect viewport = {0, 0, 1, 1};
    float width = 0;
    float height = 0;
    gfx::Color clearColor = {0.2f, 0.2f, 0.2f, 1};
    
//    gfx::Device *device = nullptr;
////    scene: RenderScene | null = null;
////    node: Node | null = null;
//    String name;
//    bool enabled = false;
////    proj: CameraProjection = -1;
//    float aspect = 0;
//    float orthoHeight = 10.0f;
////    fovAxis = CameraFOVAxis.VERTICAL;
//    fov: number = toRadian(45);
//    nearClip: number = 1.0;
//    farClip: number = 1000.0;
//    clearColor: IGFXColor = { r: 0.2, g: 0.2, b: 0.2, a: 1 };
//    viewport: Rect = new Rect(0, 0, 1, 1);
//    isProjDirty = true;
//    matView: Mat4 = new Mat4();
//    matViewInv: Mat4 | null = null;
//    matProj: Mat4 = new Mat4();
//    matProjInv: Mat4 = new Mat4();
//    matViewProj: Mat4 = new Mat4();
//    matViewProjInv: Mat4 = new Mat4();
//    frustum: frustum = new frustum();
//    forward: Vec3 = new Vec3();
//    position: Vec3 = new Vec3();
//    view: RenderView | null = null;
//    visibility = CAMERA_DEFAULT_MASK;
//    priority: number = 0;
//    aperture: CameraAperture = CameraAperture.F16_0;
//    apertureValue: number;
//    shutter: CameraShutter = CameraShutter.D125;
//    shutterValue: number = 0.0;
//    iso: CameraISO = CameraISO.ISO100;
//    isoValue: number = 0.0;
//    ec: number = 0.0;
//    exposure: number = 0.0;
};

} //namesapce scene
} //namespace cc
