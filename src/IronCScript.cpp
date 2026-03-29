#include "IronCScript.h"
#include "IronCScriptImpl.h"
#include "backend/ScriptFunctionRegistry.h"

namespace cse {

IronCScript::IronCScript()
    : m_pImpl(std::make_unique<IronCScriptImpl>())
{
}

IronCScript::~IronCScript() = default;

IronCScript::IronCScript(IronCScript&& other) noexcept
    : m_pImpl(std::move(other.m_pImpl))
{
}

IronCScript& IronCScript::operator=(IronCScript&& other) noexcept {
    if (this != &other) {
        m_pImpl = std::move(other.m_pImpl);
    }
    return *this;
}

bool IronCScript::execute(const std::string& scriptCode) {
    return m_pImpl->execute(scriptCode);
}

bool IronCScript::executeFile(const std::string& filePath) {
    return m_pImpl->executeFile(filePath);
}

int IronCScript::getLastReturnValue() const {
    return m_pImpl->getLastReturnValue();
}

std::string IronCScript::getLastError() const {
    return m_pImpl->getLastError();
}

void IronCScript::setStandardOutputCallback(ExecutionCallback callback) {
    m_pImpl->setStandardOutputCallback(std::move(callback));
}

void IronCScript::setStandardErrorCallback(ExecutionCallback callback) {
    m_pImpl->setStandardErrorCallback(std::move(callback));
}

bool IronCScript::registerNativeFunction(const std::string& name, void* funcPtr) {
    return m_pImpl->registerNativeFunction(name, funcPtr);
}

std::string IronCScript::getPlatformName() const {
    return m_pImpl->getPlatformName();
}

void IronCScript::setPlatform(const std::string& platformName) {
    m_pImpl->setPlatform(platformName);
}

std::string IronCScript::version() {
    return "1.0.0";
}

std::string IronCScript::supportedPlatforms() {
    return "x86-64, riscv64";
}

void* IronCScript::getRegisteredCallback(const std::string& name) {
    return ScriptFunctionRegistry::instance().getScriptFunction(name);
}

bool IronCScript::hasRegisteredCallback(const std::string& name) const {
    return ScriptFunctionRegistry::instance().hasFunction(name);
}

void IronCScript::setCacheEnabled(bool enabled) {
    m_pImpl->setCacheEnabled(enabled);
}

void IronCScript::setForceRecompile(bool force) {
    m_pImpl->setForceRecompile(force);
}

bool IronCScript::clearCache(const std::string& filePath) {
    return m_pImpl->clearCache(filePath);
}

} // namespace cse