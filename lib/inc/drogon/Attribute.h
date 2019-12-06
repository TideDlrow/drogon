/**
 *
 *  Attribute.h
 *  armstrong@sweelia.com
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  https://github.com/an-tao/drogon
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 *
 */

#pragma once

#include <drogon/utils/any.h>
#include <trantor/utils/Logger.h>
#include <map>
#include <memory>

namespace drogon
{
/**
 * @brief This class represents a attribute stored in the request context.
 * One can get or set any type of data to a attribute object.
 */
class Attributes
{
  public:
    /**
     * @brief Get the data identified by the key parameter.
     * @note if the data is not found, a default value is returned.
     * For example:
     * @code
       auto &userName = attributesPtr->get<std::string>("user name");
       @endcode
     */
    template <typename T>
    const T &get(const std::string &key) const
    {
        const static T nullVal = T();
        auto it = attributesMap_.find(key);
        if (it != attributesMap_.end())
        {
            if (typeid(T) == it->second.type())
            {
                return *(any_cast<T>(&(it->second)));
            }
            else
            {
                LOG_ERROR << "Bad type";
            }
        }
        return nullVal;
    }

    /**
     * @brief Get the 'any' object identified by the given key
     */
    any &operator[](const std::string &key)
    {
        return attributesMap_[key];
    }

    /**
     * @brief Insert a key-value pair
     * @note here the any object can be created implicitly. for example
     * @code
       attributesPtr->insert("user name", userNameString);
       @endcode
     */
    void insert(const std::string &key, const any &obj)
    {
        attributesMap_[key] = obj;
    }

    /**
     * @brief Insert a key-value pair
     * @note here the any object can be created implicitly. for example
     * @code
       attributesPtr->insert("user name", userNameString);
       @endcode
     */
    void insert(const std::string &key, any &&obj)
    {
        attributesMap_[key] = std::move(obj);
    }

    /**
     * @brief Erase the data identified by the given key.
     */
    void erase(const std::string &key)
    {
        attributesMap_.erase(key);
    }

    /**
     * @brief Retrun true if the data identified by the key exists.
     */
    bool find(const std::string &key)
    {
        if (attributesMap_.find(key) == attributesMap_.end())
        {
            return false;
        }
        return true;
    }

    /**
     * @brief Clear all attributes.
     */
    void clear()
    {
        attributesMap_.clear();
    }

    /**
     * @brief Constructor, usually called by the framework
     */
    Attributes()
    {
    }

  private:
    using AttributesMap = std::map<std::string, any>;
    AttributesMap attributesMap_;
};

using AttributesPtr = std::shared_ptr<Attributes>;

}  // namespace drogon