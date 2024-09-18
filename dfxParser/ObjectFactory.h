#pragma once
class ObjectFactory {
protected:
    template <typename T, typename... Args>
    static T* createObject(std::vector<double>& values) {
        return createObjectHelper<T>(values, std::index_sequence_for<Args...>{});
    }

private:
    template <typename T, size_t... index>
    static T* createObjectHelper(std::vector<double>& values, std::index_sequence<index...>) {
        return new T(values[index]...);
    }
};

