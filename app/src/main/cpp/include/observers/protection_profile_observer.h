class ProtectionProfileObserverImpl final : public mip::ProtectionProfile::Observer {
public:
virtual void OnLoadSuccess(
    const shared_ptr<mip::ProtectionProfile>& profile,
    const shared_ptr<void>& context) override {
    auto loadPromise = static_cast<promise<shared_ptr<mip::ProtectionProfile>>*>(context.get());
    loadPromise->set_value(profile);
}

virtual void OnLoadFailure(const exception_ptr& error, const shared_ptr<void>& context) override {
  auto loadPromise = static_cast<promise<shared_ptr<mip::ProtectionProfile>>*>(context.get());
  loadPromise->set_exception(error);
}

virtual void OnAddEngineSuccess(
    const shared_ptr<mip::ProtectionEngine>& engine,
    const shared_ptr<void>& context) override {
  auto addEnginePromise = static_cast<promise<shared_ptr<mip::ProtectionEngine>>*>(context.get());
  addEnginePromise->set_value(engine);
}

virtual void OnAddEngineFailure(
    const exception_ptr& error,
    const shared_ptr<void>& context) override {
  auto addEnginePromise = static_cast<promise<shared_ptr<mip::ProtectionEngine>>*>(context.get());
  addEnginePromise->set_exception(error);
  }
};

class ProtectionHandlerObserverImpl final : public mip::ProtectionHandler::Observer {
public:
  virtual void OnCreateProtectionHandlerSuccess(
      const shared_ptr<mip::ProtectionHandler>& protectionHandler,
      const shared_ptr<void>& context) override {
    auto createProtectionHandlerPromise = static_cast<promise<shared_ptr<mip::ProtectionHandler>>*>(context.get());
    createProtectionHandlerPromise->set_value(protectionHandler);
  }

  virtual void OnCreateProtectionHandlerFailure(
      const exception_ptr& error,
      const shared_ptr<void>& context) override {
    auto createProtectionHandlerPromise = static_cast<promise<shared_ptr<mip::ProtectionHandler>>*>(context.get());
    createProtectionHandlerPromise->set_exception(error);
  }
};
