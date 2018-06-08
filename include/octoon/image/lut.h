#ifndef OCTOON_IMAGE_LUT_H_
#define OCTOON_IMAGE_LUT_H_

#include <limits>
#include <sstream>
#include <fstream>

namespace octoon
{
	namespace image
	{
		namespace detail
		{
			class exception : public std::exception
			{
			public:
				virtual const char* what() const noexcept override
				{
					return m.what();
				}

				const int id;

			protected:
				exception(int id_, const char* what_arg)
					: id(id_), m(what_arg)
				{}

				static std::string name(const std::string& ename, int id)
				{
					return "[lut.exception." + ename + "." + std::to_string(id) + "] ";
				}

			private:
				std::runtime_error m;
			};

			class parse_error : public exception
			{
			public:
				static parse_error create(int id, size_t byte_, const std::string& what_arg)
				{
					std::string w = exception::name("parse_error", id) + "parse error" + (byte_ != 0 ? (" at " + std::to_string(byte_)) : "") + ": " + what_arg;
					return parse_error(id, byte_, w.c_str());
				}

				const size_t byte;

			private:
				parse_error(int id_, size_t byte_, const char* what_arg)
					: exception(id_, what_arg), byte(byte_)
				{
				}
			};

			template<typename T>
			struct Vector2
			{
				T x, y;

				Vector2() = default;
				Vector2(T xx, T yy) noexcept :x(xx), y(yy) {}

				Vector2& operator+=(T scale) noexcept { x += scale; y += scale; return *this; }
				Vector2& operator-=(T scale) noexcept { x -= scale; y -= scale; return *this; }
				Vector2& operator*=(T scale) noexcept { x *= scale; y *= scale; return *this; }
				Vector2& operator/=(T scale) noexcept { x /= scale; y /= scale; return *this; }

				Vector2& operator+=(const Vector2& r) noexcept { x += r.x; y += r.y; return *this; }
				Vector2& operator-=(const Vector2& r) noexcept { x -= r.x; y -= r.y; return *this; }
				Vector2& operator*=(const Vector2& r) noexcept { x *= r.x; y *= r.y; return *this; }
				Vector2& operator/=(const Vector2& r) noexcept { x /= r.x; y /= r.y; return *this; }

				friend Vector2 operator+(const Vector2& l, const Vector2& r) noexcept { return Vector2(l.x + r.x, l.y + r.y); }
				friend Vector2 operator-(const Vector2& l, const Vector2& r) noexcept { return Vector2(l.x - r.x, l.y - r.y); }
				friend Vector2 operator*(const Vector2& l, const Vector2& r) noexcept { return Vector2(l.x * r.x, l.y * r.y); }
				friend Vector2 operator/(const Vector2& l, const Vector2& r) noexcept { return Vector2(l.x / r.x, l.y / r.y); }

				template<typename S>
				friend Vector2 operator+(const Vector2& l, S scale) noexcept { return Vector2(l.x + scale, l.y + scale); }
				template<typename S>
				friend Vector2 operator-(const Vector2& l, S scale) noexcept { return Vector2(l.x - scale, l.y - scale); }
				template<typename S>
				friend Vector2 operator*(const Vector2& l, S scale) noexcept { return Vector2(l.x * scale, l.y * scale); }
				template<typename S>
				friend Vector2 operator/(const Vector2& l, S scale) noexcept { return Vector2(l.x / scale, l.y / scale); }

				const T operator[](std::uint8_t i) const noexcept
				{
					assert(i < 2);
					return *(&x + i);
				}

				const T& operator[](std::uint8_t i) noexcept
				{
					assert(i < 2);
					return *(&x + i);
				}
			};

			template<typename T>
			struct Vector3
			{
				T x, y, z;

				Vector3() = default;
				Vector3(T xx, T yy, T zz) noexcept :x(xx), y(yy), z(zz) {}

				Vector3& operator+=(const Vector3& r) noexcept { x += r.x; y += r.y; z += r.z; return *this; }
				Vector3& operator-=(const Vector3& r) noexcept { x -= r.x; y -= r.y; z -= r.z; return *this; }
				Vector3& operator*=(const Vector3& r) noexcept { x *= r.x; y *= r.y; z *= r.z; return *this; }
				Vector3& operator/=(const Vector3& r) noexcept { x /= r.x; y /= r.y; z /= r.z; return *this; }

				template<typename S>
				friend Vector3 operator+(const Vector3& l, S scale) noexcept { return Vector3(l.x + scale, l.y + scale, l.z + scale); }
				template<typename S>
				friend Vector3 operator-(const Vector3& l, S scale) noexcept { return Vector3(l.x - scale, l.y - scale, l.z - scale); }
				template<typename S>
				friend Vector3 operator*(const Vector3& l, S scale) noexcept { return Vector3(l.x * scale, l.y * scale, l.z * scale); }
				template<typename S>
				friend Vector3 operator/(const Vector3& l, S scale) noexcept { return Vector3(l.x / scale, l.y / scale, l.z / scale); }

				friend Vector3 operator+(const Vector3& l, const Vector3& r) noexcept { return Vector3(l.x + r.x, l.y + r.y, l.z + r.z); }
				friend Vector3 operator-(const Vector3& l, const Vector3& r) noexcept { return Vector3(l.x - r.x, l.y - r.y, l.z - r.z); }
				friend Vector3 operator*(const Vector3& l, const Vector3& r) noexcept { return Vector3(l.x * r.x, l.y * r.y, l.z * r.z); }
				friend Vector3 operator/(const Vector3& l, const Vector3& r) noexcept { return Vector3(l.x / r.x, l.y / r.y, l.z / r.z); }

				const T operator[](std::uint8_t i) const noexcept
				{
					assert(i < 3);
					return *(&x + i);
				}

				const T& operator[](std::uint8_t i) noexcept
				{
					assert(i < 3);
					return *(&x + i);
				}
			};

			template<typename T>
			struct Vector4
			{
				T x, y, z, w;

				Vector4() = default;
				Vector4(T xx, T yy, T zz, T ww) noexcept :x(xx), y(yy), z(zz), w(ww) {}

				Vector4& operator+=(const Vector4& r) noexcept { x += r.x; y += r.y; z += r.z; w += r.w; return *this; }
				Vector4& operator-=(const Vector4& r) noexcept { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this; }
				Vector4& operator*=(const Vector4& r) noexcept { x *= r.x; y *= r.y; z *= r.z; w *= r.w; return *this; }
				Vector4& operator/=(const Vector4& r) noexcept { x /= r.x; y /= r.y; z /= r.z; w /= r.w; return *this; }

				friend Vector4 operator+(const Vector4& l, const Vector4& r) noexcept { return Vector4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w); }
				friend Vector4 operator-(const Vector4& l, const Vector4& r) noexcept { return Vector4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w); }
				friend Vector4 operator*(const Vector4& l, const Vector4& r) noexcept { return Vector4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w); }
				friend Vector4 operator/(const Vector4& l, const Vector4& r) noexcept { return Vector4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w); }

				const T operator[](std::uint8_t i) const noexcept
				{
					assert(i < 4);
					return *(&x + i);
				}

				const T& operator[](std::uint8_t i) noexcept
				{
					assert(i < 4);
					return *(&x + i);
				}
			};

			template<typename T, typename = std::enable_if_t<std::is_integral<T>::value | std::is_unsigned<T>::value | std::is_floating_point<T>::value>>
			class basic_lut
			{
			public:
				std::string name;

				std::uint32_t width;
				std::uint32_t height;
				std::uint8_t channel;
				std::unique_ptr<T[]> data;

				basic_lut() noexcept {};

				/*
				* @brief ����3D lut ���ұ�
				* @param[in] data 3D lut ���ұ��������Ϣ
				* @param[in] w ͼƬ���
				* @param[in] h ͼƬ�߶�
				* @param[in] c ͨ������, RGB = 3, RGBA = 4
				*/
				basic_lut(std::unique_ptr<T>&& _data, std::uint32_t w, std::uint32_t h, std::uint8_t c) noexcept : data(std::move(_data)), width(w), height(h), channel(c) {}

				/*
				* @brief ����3D lut ���ұ�
				* @param[in] s .cube�ļ�����ʼ����
				* @param[in] n .cube�ļ��ĳ���
				* @details ����cube�ļ���������һ��3D lut ���ұ�
				*/
				basic_lut(const char* s, std::size_t n) noexcept(false) { this->create(s, n); }

				/*
				* @brief ����Ĭ�ϵ� 3D lut ���ұ�, �����Զ����˾�Ч��
				* @param[in] size ���ұ�Ĵ�С�����Ϊ size * size�� �߶�Ϊ size
				* @param[in] channel ͨ�������� RGB Ϊ 3�� RGBA Ϊ 4
				* @details ����Ĭ�ϵ� 3D lut ���ұ�, �����Զ����˾�Ч��
				*/
				explicit basic_lut(std::uint32_t size, std::uint8_t channel_ = 3) noexcept { this->create(size, channel_); }

				/*
				* @brief ����3D lut ���ұ�
				* @param[in] strean .cube�ļ�����
				* @details ����cube����������һ��3D lut ���ұ�
				*/
				explicit basic_lut(std::istream& stream) noexcept(false) { this->create(stream); }

				/*
				* @brief ����Ĭ�ϵ� 3D lut ���ұ�, �����Զ����˾�Ч��
				* @param[in] size ���ұ�Ĵ�С�����Ϊ size * size�� �߶�Ϊ size
				* @param[in] channel ͨ�������� RGB Ϊ 3�� RGBA Ϊ 4
				* @details ����Ĭ�ϵ� 3D lut ���ұ�, �����Զ����˾�Ч��
				*/
				void create(std::uint32_t size, std::uint8_t channel_) noexcept
				{
					width = size * size;
					height = size;
					channel = channel_;
					data = std::make_unique<T[]>(width * height * channel);

					for (std::uint32_t x = 0; x < width; x++)
					{
						for (std::uint32_t y = 0; y < height; y++)
						{
							float u = float(x) / (width - 1) * ((width - 1.0f) / width);
							float v = float(y) / (height - 1) * ((height - 1.0f) / height);

							float uvw[3];
							uvw[0] = frac(u * size);
							uvw[1] = v;
							uvw[2] = u - uvw[0] / size;

							uvw[0] *= size / float(size - 1);
							uvw[1] *= size / float(size - 1);
							uvw[2] *= size / float(size - 1);

							std::size_t n = (width * y + x) * channel;
							data[n + 0] = cast<T>(uvw[0]);
							data[n + 1] = cast<T>(uvw[1]);
							data[n + 2] = cast<T>(uvw[2]);
						}
					}
				}
				
				/*
				* @brief ����3D lut ���ұ�
				* @param[in] s .cube�ļ�����ʼ����
				* @param[in] n .cube�ļ��ĳ���
				* @details ����cube�ļ���������һ��3D lut ���ұ�
				*/
				void create(const char* s, std::size_t n) noexcept(false)
				{
					this->create(std::istringstream(std::string(s, n)));
				}

				/*
				* @brief ����3D lut ���ұ�
				* @param[in] strean .cube�ļ�����
				* @details ����cube����������һ��3D lut ���ұ�
				*/
				void create(std::istream& stream) noexcept(false)
				{
					assert(stream.good());

					std::string line;
					std::uint32_t size = 0;

					std::vector<float> values;

					while (std::getline(stream, line))
					{
						if (line.empty())
							continue;

						if (line[0] == '#')
							continue;

						if (line.compare(0, 5, "TITLE") == 0)
						{
							std::string token;
							std::istringstream sin(line);

							sin >> token >> name;
							continue;
						}

						if (line.compare(0, 10, "DOMAIN_MIN") == 0 || line.compare(0, 10, "DOMAIN_MAX") == 0)
							continue;

						if (line.compare(0, 11, "LUT_3D_SIZE") == 0)
						{
							std::string token;
							std::istringstream sin(line);

							sin >> token >> size;
							continue;
						}

						float r, g, b;

						std::istringstream sin(line);
						sin >> r >> g >> b;

						values.push_back(r);
						values.push_back(g);
						values.push_back(b);
					}

					if (values.size() == size * size * size * 3)
					{
						this->width = size * size;
						this->height = size;
						this->channel = 3;
						this->data = std::make_unique<T[]>(this->width * this->height * this->channel);

						for (std::size_t y = 0; y < size; y++)
						{
							for (std::size_t z = 0; z < size; z++)
							{
								for (std::size_t x = 0; x < size; x++)
								{
									auto dst = (y * width + (z * size + x)) * this->channel;
									auto src = (z * width + (y * size + x)) * this->channel;

									this->data[dst + 0] = cast<T>(values[src + 0]);
									this->data[dst + 1] = cast<T>(values[src + 1]);
									this->data[dst + 2] = cast<T>(values[src + 2]);
								}
							}
						}
					}
					else
					{
						throw parse_error::create(0, 0, "The lut element does not match the size of lut");
					}					
				}

				/*
				* @brief ��������
				* @param[in] u x��ķ�������꣬��Χ 0.0 ~ 1.0
				* @param[in] v y��ķ�������꣬��Χ 0.0 ~ 1.0
				* @return �����ڹ�һ����������(u, v) ��ͨ������ڲ�����ȡ����������
				* @detail https://en.wikipedia.org/wiki/Nearest-neighbor_interpolation
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_floating_point<_Elem>::value, Vector3<_Elem>> fetch(_Elem u, _Elem v) noexcept
				{
					assert(this->data);
					assert(this->channel == 3 || this->channel == 4);
					assert(this->width == this->height * this->height);

					auto x = std::min(std::max(0.0f, u), 1.0f) * this->width;
					auto y = std::min(std::max(0.0f, v), 1.0f) * this->height;
					auto n = (this->width * (int)std::round(y) + (int)std::round(x)) * this->channel;

					return Vector3<T>(this->data[n], this->data[n + 1], this->data[n + 2]);
				}

				/*
				* @brief ��������
				* @param[in] u x��ķ���ľ����������꣬��Χ 0 ~ width
				* @param[in] v y��ķ���ľ����������꣬��Χ 0 ~ height
				* @return �����ھ���������������(u, v) ��ͨ������ڲ�����������
				* @detail https://en.wikipedia.org/wiki/Nearest-neighbor_interpolation
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_unsigned<_Elem>::value | std::is_integral<_Elem>::value, Vector3<_Elem>> fetch(_Elem u, _Elem v) noexcept
				{
					assert(this->data);
					assert(this->channel == 3 || this->channel == 4);
					assert(this->width == this->height * this->height);

					auto x = std::min(std::max(0, u), this->width);
					auto y = std::min(std::max(0, v), this->height);
					auto n = (this->width * y + x) * this->channel;

					return Vector3<T>(this->data[n], this->data[n + 1], this->data[n + 2]);
				}

				/*
				* @brief ˫���Թ��˲���
				* @param[in] u x��ķ���Ĺ�һ�����꣬��Χ 0.0 ~ 1.0
				* @param[in] v y��ķ���Ĺ�һ�����꣬��Χ 0.0 ~ 1.0
				* @return �����ڹ�һ����������(u, v) ��ͨ��˫���Բ�����ȡ����������
				* @detail https://en.wikipedia.org/wiki/Bilinear_interpolation#Alternative_algorithm
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_floating_point<_Elem>::value, Vector3<_Elem>> lookup(_Elem u, _Elem v) noexcept
				{
					assert(u >= 0.0f && u <= 1.0f);
					assert(v >= 0.0f && v <= 1.0f);
					assert(this->data);
					assert(this->channel == 3 || this->channel == 4);
					assert(this->width == this->height * this->height);

					_Elem x = std::min(std::max(0.0f, u), 1.0f) * this->width;
					_Elem y = std::min(std::max(0.0f, v), 1.0f) * this->height;
					_Elem x2 = x >= this->width - 1 ? this->width - 1 : x + 1;
					_Elem y2 = y >= this->height - 1 ? this->height - 1 : y + 1;

					_Elem xw = frac(x);
					_Elem yw = frac(y);

					// linear interpolation
					_Elem xw1 = 1.0f - xw;
					_Elem xw2 = xw;
					_Elem yw1 = 1.0f - yw;
					_Elem yw2 = yw;

					auto n1 = (this->width * (int)y + (int)x) * this->channel;
					auto n2 = (this->width * (int)y + (int)x2) * this->channel;
					auto n3 = (this->width * (int)y2 + (int)x) * this->channel;
					auto n4 = (this->width * (int)y2 + (int)x2) * this->channel;

					auto v1 = Vector3<_Elem>(this->data[n1], this->data[n1 + 1], this->data[n1 + 2]);
					auto v2 = Vector3<_Elem>(this->data[n2], this->data[n2 + 1], this->data[n2 + 2]);
					auto v3 = Vector3<_Elem>(this->data[n3], this->data[n3 + 1], this->data[n3 + 2]);
					auto v4 = Vector3<_Elem>(this->data[n4], this->data[n4 + 1], this->data[n4 + 2]);

					v1 = v1 * xw1 * yw1;
					v2 = v2 * xw2 * yw1;
					v3 = v3 * xw1 * yw2;
					v4 = v4 * xw2 * yw2;

					return v1 + v2 + v3 + v4;
				}

				/*
				* @brief ˫���Թ��˲���
				* @param[in] u x��ķ����������Χ��δ��һ�����꣬��Χ 0 ~ ���������������ֵ
				* @param[in] v y��ķ����������Χ��δ��һ�����꣬��Χ 0 ~ ���������������ֵ
				* @return ������������Χ��δ��һ����������(u, v) ��ͨ��˫���Բ�����ȡ����������
				* @detail https://en.wikipedia.org/wiki/Bilinear_interpolation#Alternative_algorithm
				*/
				template<typename _Elem, typename _Float = float>
				std::enable_if_t<std::is_integral<_Elem>::value | std::is_unsigned<_Elem>::value, Vector3<_Elem>> lookup(const _Elem u, const _Elem v)
				{
					auto uu = (_Float)u / std::numeric_limits<_Elem>::max();
					auto vv = (_Float)v / std::numeric_limits<_Elem>::max();
					auto pixel = lookup(uu, vv);
					return Vector3<_Elem>(cast<_Elem, T>(pixel[0]), cast<_Elem, T>(pixel[1]), cast<_Elem, T>(pixel[2]));
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] u x��ķ���Ĺ�һ�����������꣬��Χ 0.0 ~ 1.0
				* @param[in] v y��ķ���Ĺ�һ�����������꣬��Χ 0.0 ~ 1.0
				* @param[in] w z��ķ���Ĺ�һ�����������꣬��Χ 0.0 ~ 1.0
				* @return �����ڹ�һ����������������(u, v, w) ��ͨ��˫���Բ�����ȡ����������
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_floating_point<_Elem>::value, Vector3<_Elem>> lookup(const _Elem u, const _Elem v, const _Elem w)
				{
					assert(u >= 0.0f && u <= 1.0f);
					assert(v >= 0.0f && v <= 1.0f);
					assert(w >= 0.0f && w <= 1.0f);
					assert(this->data);
					assert(this->channel == 3 || this->channel == 4);
					assert(this->width == this->height * this->height);

					_Elem c[3];
					c[0] = u * ((this->height - 1.0f) / this->height);
					c[1] = v * ((this->height - 1.0f) / this->height);
					c[2] = w * ((this->height - 1.0f) / this->height);

					_Elem slice = c[2] * this->height - 0.5f;
					_Elem s = frac(slice);
					slice -= s;

					_Elem uu = std::max<_Elem>(0.0f, c[0] + slice) / this->height;
					_Elem vv = std::max<_Elem>(0.0f, c[1]);

					_Elem uv0[] = { uu, vv };
					_Elem uv1[] = { uu + 1.0f / this->height, vv };

					auto col0 = lookup(uv0[0], uv0[1]);
					auto col1 = lookup(uv1[0], uv1[1]);

					return lerp(col0, col1, s);
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] u x��ķ����������Χ��δ��һ�����������꣬��Χ 0 ~ ���������������ֵ
				* @param[in] v y��ķ����������Χ��δ��һ�����������꣬��Χ 0 ~ ���������������ֵ
				* @param[in] w z��ķ����������Χ��δ��һ�����������꣬��Χ 0 ~ ���������������ֵ
				* @return ������������Χ��δ��һ����������������(u, v, w) ��ͨ��˫���Բ�����ȡ����������
				*/
				template<typename _Elem, typename _Float = float>
				std::enable_if_t<std::is_integral<_Elem>::value | std::is_unsigned<_Elem>::value, Vector3<_Elem>> lookup(const _Elem u, const _Elem v, const _Elem w)
				{
					auto uu = (_Float)u / std::numeric_limits<_Elem>::max();
					auto vv = (_Float)v / std::numeric_limits<_Elem>::max();
					auto ww = (_Float)w / std::numeric_limits<_Elem>::max();
					auto pixel = lookup(uu, vv, ww);
					return Vector3<_Elem>(cast<_Elem, T>((T)pixel[0]), cast<_Elem, T>((T)pixel[1]), cast<_Elem, T>((T)pixel[2]));
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] uvw[0] x��ķ���Ĺ�һ�����������꣬��Χ 0.0 ~ 1.0
				* @param[in] uvw[1] y��ķ���Ĺ�һ�����������꣬��Χ 0.0 ~ 1.0
				* @param[in] uvw[2] z��ķ���Ĺ�һ�����������꣬��Χ 0.0 ~ 1.0
				* @return �����ڹ�һ����������������(u, v, w) ��ͨ��˫���Բ�����ȡ����������
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_floating_point<_Elem>::value, Vector3<_Elem>> lookup(const _Elem uvw[3])
				{
					return lookup(uvw[0], uvw[1], uvw[2]);
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] uvw[0] x��ķ����������Χ��δ��һ�����������꣬��Χ 0 ~ ���������������ֵ
				* @param[in] uvw[1] y��ķ����������Χ��δ��һ�����������꣬��Χ 0 ~ ���������������ֵ
				* @param[in] uvw[2] z��ķ����������Χ��δ��һ�����������꣬��Χ 0 ~ ���������������ֵ
				* @return ������������Χ��δ��һ����������������(u, v, w) ��ͨ��˫���Բ�����ȡ����������
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_integral<_Elem>::value | std::is_unsigned<_Elem>::value, Vector3<_Elem>> lookup(const _Elem uvw[3])
				{
					return lookup(uvw[0], uvw[1], uvw[2]);
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] uvw  ��һ���������������� (u, v, w)����Χ 0.0 ~ 1.0
				* @param[out] out ��һ���������������� (u, v, w) ��ͨ��˫���Բ�����ȡ����������
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_floating_point<_Elem>::value> lookup(const _Elem uvw[3], _Elem out[3])
				{
					auto v = lookup(uvw);
					out[0] = v[0];
					out[1] = v[1];
					out[2] = v[2];
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] uvw  ������Χ��δ��һ���������������� (u, v, w)����Χ 0.0 ~ ���������������ֵ
				* @param[out] out ������Χ��δ��һ���������������� (u, v, w) ��ͨ��˫���Բ�����ȡ����������
				*/
				template<typename _Elem, typename _Float = float>
				std::enable_if_t<std::is_integral<_Elem>::value | std::is_unsigned<_Elem>::value> lookup(const _Elem uvw[3], _Elem out[3])
				{
					auto v = lookup<_Elem, _Float>(uvw[0], uvw[1], uvw[2]);
					out[0] = v[0];
					out[1] = v[1];
					out[2] = v[2];
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] uvw  ��һ���������������� (u, v, w)����Χ 0 ~ 1.0f
				* @param[out] out ��һ���������������� (u, v, w) ��ͨ��˫���Բ�����ȡ����������
				* @param[in] len ��������������ĳ���
				* @param[in] channel ���������������ͨ������, RGB = 3, RGBA = 4
				*/
				template<typename _Elem>
				std::enable_if_t<std::is_floating_point<_Elem>::value> lookup(const _Elem* uvw, _Elem* out, std::size_t len, std::uint8_t channel = 3)
				{
					assert(channel == 3 || channel == 4);

					for (std::size_t i = 0; i < len; i += channel)
						lookup(uvw + i, out + i);
				}

				/*
				* @brief �����������˫���Թ��˲���
				* @param[in] uvw  ������Χ��δ��һ���������������� (u, v, w)����Χ 0 ~ ���������������ֵ
				* @param[out] out ������Χ��δ��һ���������������� (u, v, w) ��ͨ��˫���Բ�����ȡ����������
				* @param[in] len ��������������ĳ���
				* @param[in] channel ���������������ͨ������, RGB = 3, RGBA = 4
				*/
				template<typename _Elem, typename _Float = float>
				std::enable_if_t<std::is_integral<_Elem>::value | std::is_unsigned<_Elem>::value> lookup(const _Elem* uvw, _Elem* out, std::size_t len, std::uint8_t channel = 3)
				{
					assert(channel == 3 || channel == 4);

					for (std::size_t i = 0; i < len; i += channel)
						lookup<_Elem, _Float>(uvw + i, out + i);
				}

				/*
				* @brief ��lut�е��������л���.cube���ַ�����
				*/
				std::string dump() const noexcept
				{
					assert(this->data);
					assert(this->channel == 3 || this->channel == 4);
					assert(this->width == this->height * this->height);

					std::ostringstream stream;

					stream << "TITLE " << name << std::endl;
					stream << std::endl;

					stream << "LUT_3D_SIZE " << this->height << std::endl;
					stream << std::endl;

					stream << "DOMAIN_MIN 0.0 0.0 0.0" << std::endl;
					stream << "DOMAIN_MAX 1.0 1.0 1.0" << std::endl;
					stream << std::endl;

					for (std::size_t y = 0; y < this->height; y++)
					{
						for (std::size_t z = 0; z < this->height; z++)
						{
							for (std::size_t x = 0; x < this->height; x++)
							{
								auto src = (z * width + (y * this->height + x)) * this->channel;
								auto r = cast<float>(data[src + 0]);
								auto g = cast<float>(data[src + 1]);
								auto b = cast<float>(data[src + 2]);

								stream << r << " " << g << " " << b << std::endl;
							}
						}
					}

					return stream.str();
				}

				/*
				* @brief ����һ������cube�ļ�����
				*/
				static basic_lut parse(std::istream& stream) noexcept(false)
				{
					if (stream)
						return basic_lut(stream);
					else
						throw std::runtime_error("bad stream");
				}

				/*
				* @brief ����һ������cube���ļ�
				*/
				static basic_lut parse(const std::string& filepath) noexcept(false)
				{
					auto stream = std::ifstream(filepath);
					if (stream)
						return basic_lut(stream);
					else
						throw std::runtime_error("failed to open the file: " + filepath);
				}

				/*
				* @brief ����һ������cube���ļ�
				*/
				static basic_lut parse(const char* filepath) noexcept(false)
				{
					auto stream = std::ifstream(filepath);
					if (stream)
						return basic_lut(stream);
					else
						throw std::runtime_error(std::string("failed to open the file: ") + filepath);
				}

				/*
				* @brief ��lut�е��������л���.cube���ַ�����
				*/
				friend std::ostream& operator << (std::ostream& os, const basic_lut& lut) noexcept
				{
					os << lut.dump();
					return os;
				}

			private:
				template<typename _Tx, typename _Ty>
				static std::enable_if_t<std::is_same<_Tx, _Ty>::value, _Tx> cast(_Ty x) noexcept
				{
					return x;
				}

				/*
				* @brief ��������һ���ɸ�����
				*/
				template<typename _Tx, typename _Ty, typename = std::enable_if_t<std::is_integral<_Ty>::value | std::is_unsigned<_Ty>::value, _Tx>>
				static std::enable_if_t<std::is_floating_point<_Tx>::value, _Tx> cast(_Ty x) noexcept
				{
					return static_cast<_Tx>(_Tx(x) / std::numeric_limits<_Ty>::max());
				}

				/*
				* @brief �������������������ֵ
				*/
				template<typename _Tx, typename _Ty, typename = std::enable_if_t<std::is_floating_point<_Ty>::value>>
				static std::enable_if_t<std::is_integral<_Tx>::value | std::is_unsigned<_Tx>::value, _Tx> cast(_Ty x) noexcept
				{
					return static_cast<_Tx>(std::min(std::max(x, 0.0f), 1.0f) * std::numeric_limits<_Tx>::max());
				}

				/*
				* @brief ȡС������
				*/
				template<typename _Tx>
				static _Tx frac(const _Tx x) noexcept
				{
					return x - std::floor(x);
				}

				/*
				* @brief ��t1 �� t2 ֮��������Բ�ֵ
				* @param[in] t1 ��ʼֵ
				* @param[in] t2 ��ֵֹ
				* @param[in] t3 ��ֵ�İٷֱȣ���Χ 0.0f ~ 1.0f
				*/
				template<typename _Tx, typename _Ty>
				static _Tx lerp(const _Tx t1, const _Tx t2, const _Ty t3) noexcept
				{
					if (t3 == 0) return t1; // float-precision
					if (t3 == 1) return t2; // float-precision
					return t1 + (t2 - t1) * t3;
				}
			};
		}

		using lut = detail::basic_lut<std::uint8_t>;
	}
}

#endif