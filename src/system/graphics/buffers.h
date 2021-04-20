#pragma once

enum class BufferItemType {
  Float,
  Float2,
  Float3,
  Float4
};

struct BufferItem {
  std::string    name;
  BufferItemType type;
  uint16_t       size;
  uint16_t       offset;

  BufferItem() {}
  BufferItem(BufferItemType _type, const std::string& _name);

  uint32_t getComponentCount() const {
    switch (type) {
      case BufferItemType::Float:    return 1;
      case BufferItemType::Float2:   return 2;
      case BufferItemType::Float3:   return 3;
      case BufferItemType::Float4:   return 4;
    }

    return 0;
  }
};

class BufferLayout {
public:
  BufferLayout();
  BufferLayout(std::initializer_list<BufferItem> items);

  uint32_t itemCount() const {
    return _items.size();
  }
  const BufferItem& itemAt(uint32_t idx) const {
    return _items[idx];
  }
  uint32_t stride() const {
    return _stride;
  }

private:
  std::vector<BufferItem> _items;
  uint32_t _stride;
};

class VertexBuffer;
typedef std::shared_ptr<VertexBuffer> VertexBufferRef;

class VertexBuffer {
public:
  ~VertexBuffer();

  unsigned int id() const {
    return _id;
  }
  const BufferLayout& layout() const {
    return _layout;
  }

  static VertexBufferRef Create(const uint8_t* data, uint32_t size, const BufferLayout& layout);

private:
  VertexBuffer() = delete;
  VertexBuffer(const VertexBuffer& buffer) = delete;

  VertexBuffer(const uint8_t* data, uint32_t size, const BufferLayout& layout);

private:
  BufferLayout _layout;
  unsigned int _id;
};

class IndexBuffer;
typedef std::shared_ptr<IndexBuffer> IndexBufferRef;

class IndexBuffer {
public:
  ~IndexBuffer();

  unsigned int id() const {
    return _id;
  }
  uint32_t count() const {
    return _count;
  }

  static IndexBufferRef Create(const uint32_t* indices, uint32_t count);

private:
  IndexBuffer() = delete;
  IndexBuffer(const IndexBuffer& buffer) = delete;

  IndexBuffer(const uint32_t* indices, uint32_t count);

private:
  unsigned int _id;
  uint32_t _count;
};

class VertexArray;
typedef std::shared_ptr<VertexArray> VertexArrayRef;

class VertexArray {
public:
  ~VertexArray();

  void bind();
  void unbind();

  const IndexBufferRef& indexBuffer() const { return _indexBuffer; }

  static VertexArrayRef Create(VertexBufferRef vertexBuffer, IndexBufferRef indexBuffer);
private:
  VertexArray() = delete;
  VertexArray(VertexBufferRef vertexBuffer, IndexBufferRef indexBuffer);

private:
  unsigned int _id;
  VertexBufferRef _vertexBuffer;
  IndexBufferRef _indexBuffer;
};
