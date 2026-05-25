#ifndef PENDINGQUEUE_H
#define PENDINGQUEUE_H

#include <queue>
#include <memory>
#include <tuple>
#include <functional>
#include <cstdio>

class IPending {
public:
    virtual void run() = 0;
    virtual ~IPending() = default;
};

template<typename Callable, typename... Args>
class Pending : public IPending {
private:
    Callable _callable;
    std::tuple<Args...> _args;

public:
    Pending(Callable callable, Args... args)
        : _callable(callable)
        , _args(std::make_tuple(args...)) {}

    virtual void run() override {
        std::apply(_callable, _args);
    }
};

class PendingQueue : private std::queue<std::unique_ptr<IPending>> {
public:
    ~PendingQueue() {
        printf("%ld pending items dropped\n", size());
    }

    template<typename Callable, typename... ArgTypes>
    void enqueue(Callable callable, ArgTypes... args) {
        using PendingType = Pending<Callable, ArgTypes...>;
        emplace(std::make_unique<PendingType>(callable, args...));
    }

    void run_one() {
        if (empty())
            return;
        front()->run();
        pop();
    }

    void run_all() {
        while (!empty())
            run_one();
    }
    
    size_t pending_count() const {
        return size();
    }
};

#endif