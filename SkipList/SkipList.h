#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_
#include <vector>
#include <chrono>
#include <random>
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;
using namespace std::chrono;

template<typename T>
class SkipList
{
private:
    static constexpr int SKIPLIST_MAX_LEVEL = 32;
    static constexpr int SKIPLIST_P = 1;    // p = 1/(SKIPLIST_P + 1)
    struct SkipNode
    {
        T value;
        vector<SkipNode*> level;
        SkipNode(const T& val, int _size = SKIPLIST_MAX_LEVEL)
            : value(val), level(_size, nullptr) {}
    };

    class const_iterator
    {
    protected:
        friend class SkipList;

        SkipNode* node;

        T& getValue()const
        {
            return node->value;
        }

        const_iterator(SkipNode* p) :node(p) {}

    public:
        const_iterator() : node(nullptr) {}

        const T& operator*()const
        {
            return getValue();
        }

        const_iterator& operator++()
        {
            node = node->level.at(0);
            return *this;
        }

        const_iterator operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator& iter)const
        {
            return node == iter.node;
        }

        bool operator!=(const const_iterator& iter)const
        {
            return !(*this == iter);
        }
    };

    class iterator : public const_iterator
    {
    protected:
        friend class SkipList;

        iterator(SkipNode* p) :const_iterator(p) {}

    public:
        iterator() {}

        T& operator*()
        {
            return const_iterator::getValue();
        }

        const T& operator*()const
        {
            return const_iterator::operator*();
        }

        iterator& operator++()
        {
            this->node = this->node->level.at(0);
            return *this;
        }

        iterator operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }
    };


    SkipNode* _head = nullptr;
    int _maxLevel = 1;
    size_t _size = 0;

    // 使用概率 SKIPLIST_P 返回一个 <= SKIPLIST_MAX_LEVEL 的层数
    static int randomLevel()
    {
        const static auto seed = static_cast<int>(duration_cast<milliseconds>
                                (steady_clock::now().time_since_epoch()).count());
        static default_random_engine engine(seed);
        static uniform_int_distribution<int> range(0, SKIPLIST_P);

        int level = 1;
        while (!range(engine) && level < SKIPLIST_MAX_LEVEL) ++level;
        return level;
    }

    // 克隆跳跃表 skip,返回克隆后的头节点
    SkipNode* clone(const SkipList& skip)
    {
        auto skip_head = skip._head;
        auto clone_head = new SkipNode(T());
        vector<SkipNode*> prev(skip._maxLevel, nullptr);
        
        while (skip_head->level.at(0))
        {
            auto curr_level = skip_head->level.at(0)->level.size();
            auto curr = new SkipNode(skip_head->level.at(0)->value, curr_level);
            for (size_t i = 0; i < curr_level; ++i)
            {
                if (prev.at(i))
                {
                    prev.at(i)->level.at(i) = curr;
                    prev.at(i) = prev.at(i)->level.at(i);
                }
                else
                {
                    clone_head->level.at(i) = curr;
                    prev.at(i) = curr;
                }
            }

            skip_head = skip_head->level.at(0);
        }

        return clone_head;
    }

    // 将跳跃表置空
    void makeEmpty()
    {
        auto temp = _head;
        while (_head)
        {
            _head = _head->level.at(0);
            delete temp;
            temp = _head;
        }
    }

    // 查找值 val,返回一个 vector,表示查找路径
    vector<SkipNode*> search(SkipNode*, const T& val)const
    {
        auto curr = _head;
        vector<SkipNode*> prev(SKIPLIST_MAX_LEVEL);
        for (int i = _maxLevel - 1; i >= 0; --i)
        {
            while (curr->level.at(i) && curr->level.at(i)->value < val)
                curr = curr->level.at(i);
            prev.at(i) = curr;
        }
        return prev;
    }

    // 插入节点 curr 
    void insert(SkipNode* curr, int level)
    {
        auto prev = search(_head, curr->value);
        if (level > _maxLevel)
        {
            for (int i = _maxLevel; i < level; ++i) prev.at(i) = _head;
            _maxLevel = level;
        }

        for (int i = level - 1; i >= 0; --i)
        {
            curr->level.at(i) = prev.at(i)->level.at(i);
            prev.at(i)->level.at(i) = curr;
        }
    }

    // 删除值等于 val 的一个值
    bool erase(SkipNode*, const T& val)
    {
        auto prev = search(_head, val);
        if (!prev.at(0)->level.at(0) ||
            prev.at(0)->level.at(0)->value != val) return false;

        auto del = prev.at(0)->level.at(0);
        for (int i = 0; i < _maxLevel; ++i)
        {
            if (prev.at(i)->level.at(i) == del) 
                prev.at(i)->level.at(i) = del->level.at(i);
        }
        delete del;
        del = nullptr;

        while (_maxLevel > 1 && !_head->level.at(_maxLevel - 1)) --_maxLevel;
        return true;
    }

public:
    SkipList() : _head(new SkipNode(T())) {}

    SkipList(const SkipList& skip)
    {
        _head = clone(skip);
        _maxLevel = skip._maxLevel;
        _size = skip._size;
    }

    SkipList(SkipList&& skip)noexcept
        :_head(skip._head), _maxLevel(skip._maxLevel), _size(skip._size)
    {
        skip._head = nullptr;
        skip._maxLevel = 1;
        skip._size = 0;
    }

    SkipList& operator=(const SkipList& skip)
    {
        if (this != &skip)
        {
            auto temp = clone(skip);
            makeEmpty();

            _head = temp;
            _maxLevel = skip._maxLevel;
            _size = skip._size;
        }

        return *this;
    }

    SkipList& operator=(SkipList&& skip)noexcept
    {
        if (this != &skip)
        {
            _head = skip._head;
            _maxLevel = skip._maxLevel;
            _size = skip._size;

            skip._head = nullptr;
            skip._maxLevel = 1;
            skip._size = 0;
        }

        return *this;
    }

    ~SkipList()
    {
        makeEmpty();
        _head = nullptr;
        _maxLevel = 1;
        _size = 0;
    }


    bool empty()const noexcept
    {
        return _head->level.at(0) == nullptr;
    }

    size_t size()const noexcept
    {
        return _size;
    }

    iterator begin()
    {
        return iterator(_head->level.at(0));
    }

    const_iterator begin()const
    {
        return const_iterator(_head->level.at(0));
    }

    iterator end()
    {
        return iterator();
    }

    const_iterator end()const
    {
        return const_iterator();
    }


    iterator find(const T& val)
    {
        auto prev = search(_head, val);
        return iterator(prev.at(0)->level.at(0));
    }

    const_iterator find(const T& val)const
    {
        return const_iterator(find(val));
    }

    void insert(const T& val)
    {
        auto level = randomLevel();
        auto node = new SkipNode(val, level);
        if (!node) return;

        insert(node, level);
        ++_size;
    }

    void insert(T&& val)
    {
        auto level = randomLevel();
        auto node = new SkipNode(std::move(val), level);
        if (!node) return;

        insert(node, level);
        ++_size;
    }

    void erase(const T& val)
    {
        _size -= erase(_head, val);
    }

    void erase(const_iterator iter)
    {
        erase(_head, *iter);
    }

    void clear()
    {
        makeEmpty();
        _head = new SkipNode(T());
        _maxLevel = 1;
        _size = 0;
    }
};

#endif // _SKIPLIST_H_