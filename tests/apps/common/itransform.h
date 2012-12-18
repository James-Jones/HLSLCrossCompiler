#ifndef _DEMO_H_
#define _DEMO_H_

#include <vectormath_aos.h>

class ITransform {
public:
	virtual const Vectormath::Aos::Matrix4& GetWorldMatrix() const = 0;
	virtual void SetWorldMatrix(Vectormath::Aos::Matrix4& newWorld) = 0;
};

#endif
