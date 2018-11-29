#pragma once

#include "Bitmap.h"
#include "Size.h"

class Texture
{
public:
	typedef std::uint32_t handle_t;

	Texture();
	Texture(Texture&& texture);
	Texture(const Bitmap& bitmap);
	virtual ~Texture();
	Texture& operator=(Texture&& texture);
	void Dispose();
	void Bind();
	void Update(const Bitmap& bitmap);
	void Update(Rectangle area, const Bitmap& bitmap);
	void ApplyTextureFilter();
	Bitmap Download();
	Size GetSize() const;
	handle_t GetHandle() const;
	static void Enable();
	static void Disable();
	static void Unbind();
	static handle_t BoundId();

protected:
	handle_t m_handle;
	Size m_size;
	static uint32_t m_currently_bound_handle;
};