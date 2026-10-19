#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <ostream>
#include <algorithm>

class GraphException : public std::runtime_error {
public:
    explicit GraphException(const std::string& m) : std::runtime_error(m) {}
};

class VertexNotFoundException : public GraphException {
public:
    explicit VertexNotFoundException(const std::string& m)
        : GraphException("Вершина не найдена: " + m) {}
};

class EdgeNotFoundException : public GraphException {
public:
    explicit EdgeNotFoundException(const std::string& m)
        : GraphException("Ребро не найдено: " + m) {}
};

class DuplicateException : public GraphException {
public:
    explicit DuplicateException(const std::string& m)
        : GraphException("Уже существует: " + m) {}
};

template<typename T>
class Graph {
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using VertexId        = size_type;
    using EdgeId          = size_type;

    struct EdgeView {
        VertexId from;
        VertexId to;
    };

private:
    struct Vertex {
        T          data;
        size_type  firstEdge;   // индекс первого ребра или npos
        bool       alive;
    };

    struct Edge {
        VertexId   from;
        VertexId   to;
        size_type  nextFrom;    // следующее ребро в списке from
        size_type  nextTo;      // следующее ребро в списке to
        bool       alive;
    };

    static constexpr size_type npos = static_cast<size_type>(-1);

    std::vector<Vertex> vertices_;
    std::vector<Edge>   edges_;
    size_type           vCount_ = 0;
    size_type           eCount_ = 0;

public:
    class VertexIterator {
        friend class Graph;
        Graph* g_;
        size_type idx_;
        explicit VertexIterator(Graph* g, size_type i) : g_(g), idx_(i) {}
    public:
        VertexIterator() : g_(nullptr), idx_(npos) {}

        T& operator*() const {
            if (idx_ == npos) throw VertexNotFoundException("итератор");
            return g_->vertices_[idx_].data;
        }

        VertexIterator& operator++() {
            do { ++idx_; } while (idx_ < g_->vertices_.size()
                                  && !g_->vertices_[idx_].alive);
            if (idx_ >= g_->vertices_.size()) idx_ = npos;
            return *this;
        }
        VertexIterator operator++(int) { auto t = *this; ++(*this); return t; }

        VertexIterator& operator--() {
            if (idx_ == npos) idx_ = g_->vertices_.size();
            do { --idx_; } while (idx_ > 0 && !g_->vertices_[idx_].alive);
            return *this;
        }
        VertexIterator operator--(int) { auto t = *this; --(*this); return t; }

        bool operator==(const VertexIterator& o) const { return g_==o.g_ && idx_==o.idx_; }
        bool operator!=(const VertexIterator& o) const { return !(*this==o); }

        size_type index() const { return idx_; }
    };

    class ConstVertexIterator {
        friend class Graph;
        const Graph* g_;
        size_type idx_;
        explicit ConstVertexIterator(const Graph* g, size_type i) : g_(g), idx_(i) {}
    public:
        ConstVertexIterator() : g_(nullptr), idx_(npos) {}
        const T& operator*() const {
            if (idx_ == npos) throw VertexNotFoundException("итератор");
            return g_->vertices_[idx_].data;
        }
        ConstVertexIterator& operator++() {
            do { ++idx_; } while (idx_ < g_->vertices_.size()
                                  && !g_->vertices_[idx_].alive);
            if (idx_ >= g_->vertices_.size()) idx_ = npos;
            return *this;
        }
        ConstVertexIterator operator++(int) { auto t=*this; ++(*this); return t; }
        ConstVertexIterator& operator--() {
            if (idx_ == npos) idx_ = g_->vertices_.size();
            do { --idx_; } while (idx_ > 0 && !g_->vertices_[idx_].alive);
            return *this;
        }
        ConstVertexIterator operator--(int) { auto t=*this; --(*this); return t; }
        bool operator==(const ConstVertexIterator& o) const { return g_==o.g_ && idx_==o.idx_; }
        bool operator!=(const ConstVertexIterator& o) const { return !(*this==o); }
    };

    class EdgeIterator {
        friend class Graph;
        Graph* g_;
        size_type idx_;
        explicit EdgeIterator(Graph* g, size_type i) : g_(g), idx_(i) {}
    public:
        EdgeIterator() : g_(nullptr), idx_(npos) {}
        EdgeView operator*() const {
            if (idx_ == npos) throw EdgeNotFoundException("итератор");
            return { g_->edges_[idx_].from, g_->edges_[idx_].to };
        }
        EdgeIterator& operator++() {
            do { ++idx_; } while (idx_ < g_->edges_.size() && !g_->edges_[idx_].alive);
            if (idx_ >= g_->edges_.size()) idx_ = npos;
            return *this;
        }
        EdgeIterator operator++(int) { auto t=*this; ++(*this); return t; }
        EdgeIterator& operator--() {
            if (idx_ == npos) idx_ = g_->edges_.size();
            do { --idx_; } while (idx_ > 0 && !g_->edges_[idx_].alive);
            return *this;
        }
        EdgeIterator operator--(int) { auto t=*this; --(*this); return t; }
        bool operator==(const EdgeIterator& o) const { return g_==o.g_ && idx_==o.idx_; }
        bool operator!=(const EdgeIterator& o) const { return !(*this==o); }
    };

    Graph() = default;

    Graph(const Graph& other) = default;

    Graph& operator=(const Graph& other) = default;

    ~Graph() = default;

    bool empty() const { return vCount_ == 0 && eCount_ == 0; }

    void clear() {
        vertices_.clear();
        edges_.clear();
        vCount_ = 0;
        eCount_ = 0;
    }

    size_type vertexCount() const { return vCount_; }

    size_type edgeCount() const { return eCount_; }

    VertexId addVertex(const T& data) {
        for (size_type i = 0; i < vertices_.size(); ++i) {
            if (!vertices_[i].alive) {
                vertices_[i] = { data, npos, true };
                ++vCount_;
                return i;
            }
        }
        vertices_.push_back({ data, npos, true });
        ++vCount_;
        return vertices_.size() - 1;
    }

    bool hasVertex(VertexId id) const {
        return id < vertices_.size() && vertices_[id].alive;
    }

    void removeVertex(VertexId id) {
        if (!hasVertex(id)) throw VertexNotFoundException(std::to_string(id));

        for (size_type i = 0; i < edges_.size(); ++i) {
            if (edges_[i].alive &&
                (edges_[i].from == id || edges_[i].to == id)) {
                edges_[i].alive = false;
                --eCount_;
            }
        }

        vertices_[id].alive = false;
        --vCount_;
    }

    void removeVertex(VertexIterator it) { removeVertex(it.index()); }

    T& vertexData(VertexId id) {
        if (!hasVertex(id)) throw VertexNotFoundException(std::to_string(id));
        return vertices_[id].data;
    }

    size_type degree(VertexId id) const {
        if (!hasVertex(id)) throw VertexNotFoundException(std::to_string(id));
        size_type d = 0;
        for (size_type i = 0; i < edges_.size(); ++i)
            if (edges_[i].alive &&
                (edges_[i].from == id || edges_[i].to == id))
                ++d;
        return d;
    }

    EdgeId addEdge(VertexId from, VertexId to) {
        if (!hasVertex(from)) throw VertexNotFoundException(std::to_string(from));
        if (!hasVertex(to))   throw VertexNotFoundException(std::to_string(to));
        if (hasEdge(from, to)) throw DuplicateException("ребро");

        for (size_type i = 0; i < edges_.size(); ++i) {
            if (!edges_[i].alive) {
                edges_[i] = { from, to, npos, npos, true };
                linkEdge(i);
                ++eCount_;
                return i;
            }
        }
        edges_.push_back({ from, to, npos, npos, true });
        linkEdge(edges_.size() - 1);
        ++eCount_;
        return edges_.size() - 1;
    }

    bool hasEdge(VertexId a, VertexId b) const {
        for (size_type i = 0; i < edges_.size(); ++i) {
            if (!edges_[i].alive) continue;
            if ((edges_[i].from == a && edges_[i].to == b) ||
                (edges_[i].from == b && edges_[i].to == a))
                return true;
        }
        return false;
    }

    void removeEdge(VertexId a, VertexId b) {
        for (size_type i = 0; i < edges_.size(); ++i) {
            if (!edges_[i].alive) continue;
            if ((edges_[i].from == a && edges_[i].to == b) ||
                (edges_[i].from == b && edges_[i].to == a)) {
                edges_[i].alive = false;
                --eCount_;
                return;
            }
        }
        throw EdgeNotFoundException(std::to_string(a) + "-" + std::to_string(b));
    }

    void removeEdge(EdgeIterator it) {
        auto e = *it;
        removeEdge(e.from, e.to);
    }

    VertexIterator begin() {
        for (size_type i = 0; i < vertices_.size(); ++i)
            if (vertices_[i].alive) return VertexIterator(this, i);
        return VertexIterator(this, npos);
    }
    VertexIterator end() { return VertexIterator(this, npos); }

    ConstVertexIterator begin() const {
        for (size_type i = 0; i < vertices_.size(); ++i)
            if (vertices_[i].alive) return ConstVertexIterator(this, i);
        return ConstVertexIterator(this, npos);
    }
    ConstVertexIterator end() const { return ConstVertexIterator(this, npos); }

    EdgeIterator edgeBegin() {
        for (size_type i = 0; i < edges_.size(); ++i)
            if (edges_[i].alive) return EdgeIterator(this, i);
        return EdgeIterator(this, npos);
    }
    EdgeIterator edgeEnd() { return EdgeIterator(this, npos); }

    bool operator==(const Graph& o) const {
        if (vCount_ != o.vCount_ || eCount_ != o.eCount_) return false;
        // Сравнение по данным вершин и рёбрам (упрощённо)
        for (size_type i = 0; i < vertices_.size(); ++i) {
            if (vertices_[i].alive &&
                (i >= o.vertices_.size() || !o.vertices_[i].alive))
                return false;
        }
        return true;
    }
    bool operator!=(const Graph& o) const { return !(*this == o); }

    friend std::ostream& operator<<(std::ostream& os, const Graph& g) {
        os << "Graph(V=" << g.vCount_ << ", E=" << g.eCount_ << ")\n";
        for (size_type i = 0; i < g.vertices_.size(); ++i) {
            if (!g.vertices_[i].alive) continue;
            os << "  V" << i << ": " << g.vertices_[i].data;
            os << " -> [";
            bool first = true;
            for (size_type j = 0; j < g.edges_.size(); ++j) {
                if (!g.edges_[j].alive) continue;
                if (g.edges_[j].from == i || g.edges_[j].to == i) {
                    if (!first) os << ", ";
                    os << (g.edges_[j].from == i ? g.edges_[j].to
                                                 : g.edges_[j].from);
                    first = false;
                }
            }
            os << "]\n";
        }
        return os;
    }

private:
    void linkEdge(size_type eIdx) {
        auto& e = edges_[eIdx];
        e.nextFrom = vertices_[e.from].firstEdge;
        e.nextTo   = vertices_[e.to].firstEdge;
        vertices_[e.from].firstEdge = eIdx;
        vertices_[e.to].firstEdge   = eIdx;
    }
};