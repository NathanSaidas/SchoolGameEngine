#ifndef GAME_ENGINE_METHOD_INFO_H
#define GAME_ENGINE_METHOD_INFO_H

#pragma region CHANGE LOG
/// -- January, 30, 2015 - Nathan Hanlan - Added MethodInfo file and MethodInfo / MethodActionInfo classes 
#pragma region

#include "ClassMember.h"
#include "../Method.h"
#include "Runtime.h"

namespace Engine
{
    namespace Reflection
    {
        template<class CLASS, class RETURN, class ARGUMENT1 = void, class ARGUMENT2 = void, class ARGUMENT3 = void, class ARGUMENT4 = void, class ARGUMENT5 = void, class ARGUMENT6 = void, class ARGUMENT7 = void, class ARGUMENT8 = void>
        class MethodInfo : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6, ARGUMENT7, ARGUMENT8> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6, ARGUMENT7, ARGUMENT8> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6, ARGUMENT7, ARGUMENT8> m_Method;
        };
        //
        template<class CLASS, class RETURN, class ARGUMENT1, class ARGUMENT2, class ARGUMENT3, class ARGUMENT4, class ARGUMENT5, class ARGUMENT6, class ARGUMENT7>
        class MethodInfo<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6, ARGUMENT7> : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6, ARGUMENT7> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6, ARGUMENT7> m_Method;
        };
        //
        //
        template<class CLASS, class RETURN, class ARGUMENT1, class ARGUMENT2, class ARGUMENT3, class ARGUMENT4, class ARGUMENT5, class ARGUMENT6>
        class MethodInfo<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6> : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5, ARGUMENT6> m_Method;
        };
        //
        //
        template<class CLASS, class RETURN, class ARGUMENT1, class ARGUMENT2, class ARGUMENT3, class ARGUMENT4, class ARGUMENT5>
        class MethodInfo<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5> : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5> m_Method;
        };
        //
        //
        template<class CLASS, class RETURN, class ARGUMENT1, class ARGUMENT2, class ARGUMENT3, class ARGUMENT4>
        class MethodInfo<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4> : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4> m_Method;
        };
        //
        //
        template<class CLASS, class RETURN, class ARGUMENT1, class ARGUMENT2, class ARGUMENT3>
        class MethodInfo<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3> : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2, ARGUMENT3> m_Method;
        };
        //
        //
        template<class CLASS, class RETURN, class ARGUMENT1, class ARGUMENT2>
        class MethodInfo<CLASS, RETURN, ARGUMENT1, ARGUMENT2> : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1, ARGUMENT2> m_Method;
        };
        //
        //
        template<class CLASS, class RETURN, class ARGUMENT1>
        class MethodInfo<CLASS, RETURN, ARGUMENT1> : public ClassMember
        {
        public:
            MethodInfo()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN, ARGUMENT1> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN, ARGUMENT1> m_Method;
        };
        //
        //
        template<class CLASS, class RETURN>
        class MethodInfo<CLASS, RETURN> : public ClassMember
        {
        public:
            MethodInfo() : ClassMember()
            {
                m_Method = nullptr;
            }
            MethodInfo(std::string aClassName, std::string aMethodName, Method<CLASS, RETURN> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }
            Method<CLASS, RETURN> GetMethod()
            {
                return m_Method;
            }
        private:
            Method<CLASS, RETURN> m_Method;
        };
        //

        template<class CLASS, class ARGUMENT1 = void, class ARGUMENT2 = void, class ARGUMENT3 = void, class ARGUMENT4 = void, class ARGUMENT5 = void>
        class MethodActionInfo : public ClassMember
        {
        public:
            MethodActionInfo()
            {
                m_Method = nullptr;
            }

            MethodActionInfo(std::string aClassName, std::string aMethodName, MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }

            MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5> GetMethod()
            {
                return m_Method;
            }

        private:
            MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4, ARGUMENT5> m_Method;
        };

        template<class CLASS, class ARGUMENT1, class ARGUMENT2, class ARGUMENT3, class ARGUMENT4>
        class MethodActionInfo<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4> : public ClassMember
        {
        public:
            MethodActionInfo()
            {
                m_Method = nullptr;
            }

            MethodActionInfo(std::string aClassName, std::string aMethodName, MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }

            MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4> GetMethod()
            {
                return m_Method;
            }

        private:
            MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3, ARGUMENT4> m_Method;
        };

        template<class CLASS, class ARGUMENT1, class ARGUMENT2, class ARGUMENT3>
        class MethodActionInfo<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3> : public ClassMember
        {
        public:
            MethodActionInfo()
            {
                m_Method = nullptr;
            }

            MethodActionInfo(std::string aClassName, std::string aMethodName, MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }

            MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3> GetMethod()
            {
                return m_Method;
            }

        private:
            MethodAction<CLASS, ARGUMENT1, ARGUMENT2, ARGUMENT3> m_Method;
        };

        template<class CLASS, class ARGUMENT1, class ARGUMENT2>
        class MethodActionInfo<CLASS, ARGUMENT1, ARGUMENT2> : public ClassMember
        {
        public:
            MethodActionInfo()
            {
                m_Method = nullptr;
            }

            MethodActionInfo(std::string aClassName, std::string aMethodName, MethodAction<CLASS, ARGUMENT1, ARGUMENT2> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }

            MethodAction<CLASS, ARGUMENT1, ARGUMENT2> GetMethod()
            {
                return m_Method;
            }

        private:
            MethodAction<CLASS, ARGUMENT1, ARGUMENT2> m_Method;
        };

        template<class CLASS, class ARGUMENT1>
        class MethodActionInfo<CLASS, ARGUMENT1> : public ClassMember
        {
        public:
            MethodActionInfo()
            {
                m_Method = nullptr;
            }

            MethodActionInfo(std::string aClassName, std::string aMethodName, MethodAction<CLASS, ARGUMENT1> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }

            MethodAction<CLASS, ARGUMENT1> GetMethod()
            {
                return m_Method;
            }

        private:
            MethodAction<CLASS, ARGUMENT1> m_Method;
        };

        template<class CLASS>
        class MethodActionInfo<CLASS> : public ClassMember
        {
        public:
            MethodActionInfo()
            {
                m_Method = nullptr;
            }

            MethodActionInfo(std::string aClassName, std::string aMethodName, MethodAction<CLASS> aFunction)
                : ClassMember(aClassName, aMethodName)
            {
                m_Method = aFunction;
            }

            MethodAction<CLASS> GetMethod()
            {
                return m_Method;
            }

        private:
            MethodAction<CLASS> m_Method;
        };


    }
    
}

#endif