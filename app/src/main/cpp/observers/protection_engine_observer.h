using std::shared_ptr;
using std::vector;
using std::promise;
using std::string;
using std::exception_ptr;

// This observer will be notified when ProtectionEngine::GetTemplateListAsync succeeds or fails. In this case, the
// sample app passes a std::promise as the context to ProtectionProfile::LoadAsync so that the observer can set its
// value, allowing these load notifications to flow easily to app.
class ProtectionEngineObserverImpl final : public mip::ProtectionEngine::Observer {
public:
  virtual void OnGetTemplatesSuccess(
      const vector<shared_ptr<mip::TemplateDescriptor>>& templatesDescriptor,
      const shared_ptr<void>& context) override {
    auto loadPromise = static_cast<promise<vector<shared_ptr<mip::TemplateDescriptor>>>*>(context.get());
    loadPromise->set_value(templatesDescriptor);
  }

  virtual void OnGetTemplatesFailure(const exception_ptr& error, const shared_ptr<void>& context) override {
    auto loadPromise = static_cast<promise<shared_ptr<mip::ProtectionProfile>>*>(context.get());
    loadPromise->set_exception(error);
  }

  virtual void OnGetRightsForLabelIdSuccess(
      const shared_ptr<vector<string>>& rightsList,
      const shared_ptr<void>& context) override {
    auto loadPromise = static_cast<promise<shared_ptr<vector<string>>>*>(context.get());
    loadPromise->set_value(rightsList);
  }

  virtual void OnGetRightsForLabelIdFailure(const exception_ptr& error, const shared_ptr<void>& context) override {
    auto loadPromise = static_cast<promise<shared_ptr<mip::ProtectionProfile>>*>(context.get());
    loadPromise->set_exception(error);
  }

  virtual void OnLoadUserCertSuccess(const shared_ptr<void>& context) override {
    auto loadPromise = static_cast<promise<void>*>(context.get());
    loadPromise->set_value();
  }
  
  virtual void OnLoadUserCertFailure(const exception_ptr& error, const shared_ptr<void>& context) override {
    auto loadPromise = static_cast<promise<void>*>(context.get());
    loadPromise->set_exception(error);
  }
};