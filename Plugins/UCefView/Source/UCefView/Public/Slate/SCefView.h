//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file SCefView.h
//! @brief Declares the SCefView class, a Slate widget that hosts a CEF browser.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/UnrealString.h>
#include <Delegates/DelegateCombinations.h>
// Core/Public/
#include <HAL/Platform.h>
#include <Misc/Optional.h>
#include <Templates/SharedPointer.h>
// Json/Public/
#include <Dom/JsonValue.h>
// SlateCore/Public/
#include <Layout/Children.h>
#include <Widgets/DeclarativeSyntaxSupport.h>
#include <Widgets/SWidget.h>
#pragma endregion

#pragma region <Project Public Headers>
#include <CefViewTypes.h>
#include <CefContext.h>
#include <Slate/SlateCefViewSettings.h>
#pragma endregion

class SCefViewPrivate;
class CCefClientDelegate;

/// <summary>
/// A Slate widget that embeds a Chromium Embedded Framework (CEF) browser.
///
/// This widget provides methods to control browser navigation, execute JavaScript,
/// handle browser events, and manage resource mappings for local and archive files.
/// It exposes a variety of delegates for browser state changes, navigation, and
/// communication between the browser and the host application.
/// </summary>
class UCEFVIEW_API SCefView : public SWidget
{
  SLATE_DECLARE_WIDGET(SCefView, SWidget)

private:
  /// <summary>
  /// Pointer to the private implementation.
  /// </summary>
  TSharedPtr<SCefViewPrivate> m_pImpl = nullptr;

  friend class SCefViewPrivate;
  friend class CCefClientDelegate;

  /// <summary>
  /// The target URL to load in the browser.
  /// </summary>
  FString Url;

  /// <summary>
  /// Indicates whether the view should enable context menu. Enabled by default.
  /// </summary>
  bool bEnableContextMenu = true;

  /// <summary>
  ///
  /// </summary>
  bool bEnableTransparentInputPassthrough = false;

  /// <summary>
  ///
  /// </summary>
  bool bIsCefMouseInside = false;

  /// <summary>
  /// Indicates whether the view should accept drag-and-drop operations. Disabled by default.
  /// </summary>
  bool bAcceptDrops = true;

  /// <summary>
  /// Indicates whether the view should allow drag operations. Disabled by default.
  /// </summary>
  bool bAllowDrag = true;

  /// <summary>
  /// Local folder resources mapping for serving local directories as web resources.
  /// </summary>
  TArray<FLocalFolderResourceMapping> LocalFolderResourceMapping;

  /// <summary>
  /// Archive file resource mapping for serving archive files (.zip) as web resources.
  /// </summary>
  TArray<FArchiveFileResourceMapping> ArchiveFileResourceMapping;

#pragma region Type/Constans
public:
  /// <summary>
  /// The main frame identity.
  /// </summary>
  static const FCefFrameId MainFrameID;

  /// <summary>
  /// The identifier for all frames.
  /// </summary>
  static const FCefFrameId AllFrameID;

  /// <summary>
  /// The callback type of loading state changed.
  /// </summary>
  /// <param name="InBrowserId">Indicates the browser ID.</param>
  /// <param name="bInIsLoading">Indicates the browser is loading.</param>
  /// <param name="bInCanGoBack">Indicates the browser can go back.</param>
  /// <param name="bInCanGoForward">Indicates the browser can go forward.</param>
  DECLARE_DELEGATE_FourParams(FOnLoadStateChangedEvent,
                              const int64& InBrowserId,
                              bool bInIsLoading,
                              bool bInCanGoBack,
                              bool bInCanGoForward);

  /// <summary>
  /// The callback type of loading starts.
  /// </summary>
  /// <param name="InBrowserId">Indicates the browser ID.</param>
  /// <param name="InFrameId">Indicates the frame ID.</param>
  /// <param name="bInIsMainFrame">Indicates whether this is the main frame.</param>
  /// <param name="InTransitionType">Transition type.</param>
  DECLARE_DELEGATE_FourParams(FOnLoadStartEvent,
                              const int64& InBrowserId,
                              const FCefFrameId& InFrameId,
                              bool bInIsMainFrame,
                              int InTransitionType);

  /// <summary>
  /// The callback type of loading ends.
  /// </summary>
  /// <param name="InBrowserId">Indicates the browser ID.</param>
  /// <param name="InFrameId">Indicates the frame ID.</param>
  /// <param name="bInIsMainFrame">Indicates whether this is the main frame.</param>
  /// <param name="InHttpStatusCode">The HTTP status code.</param>
  DECLARE_DELEGATE_FourParams(FOnLoadEndEvent,
                              const int64& InBrowserId,
                              const FCefFrameId& InFrameId,
                              bool bInIsMainFrame,
                              int InHttpStatusCode);

  /// <summary>
  /// The callback type of loading failed due to error.
  /// </summary>
  /// <param name="InBrowserId">Indicates the browser ID.</param>
  /// <param name="InFrameId">Indicates the frame ID.</param>
  /// <param name="bInIsMainFrame">Indicates whether this is the main frame.</param>
  /// <param name="InErrorCode">The error code.</param>
  /// <param name="InErrorMsg">The error message.</param>
  /// <param name="InFailedUrl">The URL that caused the failure.</param>
  /// <param name="InOutHandled">Whether this error was handled or not.</param>
  DECLARE_DELEGATE_SevenParams(FOnLoadErrorEvent,
                               const int64& InBrowserId,
                               const FCefFrameId& InFrameId,
                               bool bInIsMainFrame,
                               int InErrorCode,
                               const FString& InErrorMsg,
                               const FString& InOutFailedUrl,
                               bool& InOutHandled);

  /// <summary>
  /// The callback type of draggable region changed.
  /// </summary>
  /// <param name="InDraggableRegion">The new draggable region.</param>
  /// <param name="InNonDraggableRegion">The new non-draggable region.</param>
  DECLARE_DELEGATE_TwoParams(FOnDraggableRegionChangedEvent,
                             const FVector4& InDraggableRegion,
                             const FVector4& InNonDraggableRegion);

  /// <summary>
  /// The callback type of the address changed.
  /// </summary>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InUrl">The address.</param>
  DECLARE_DELEGATE_TwoParams(FOnAddressChangedEvent, const FCefFrameId& InFrameId, const FString& InUrl);

  /// <summary>
  /// The callback type of title changed.
  /// </summary>
  /// <param name="InTitle">The title.</param>
  DECLARE_DELEGATE_OneParam(FOnTitleChangedEvent, const FString& InTitle);

  /// <summary>
  /// The callback type of favicon URL changed.
  /// </summary>
  /// <param name="InUrls">The URLs.</param>
  DECLARE_DELEGATE_OneParam(FOnFaviconUrlChangedEvent, const TArray<FString>& InUrls);

  /// <summary>
  /// The callback type of fullscreen mode changed.
  /// </summary>
  /// <param name="bInIsFullscreen">The current fullscreen mode.</param>
  DECLARE_DELEGATE_OneParam(FOnFullscreenModeChangedEvent, bool bInIsFullscreen);

  /// <summary>
  /// The callback type of status message changed.
  /// </summary>
  /// <param name="InMessage">The status message.</param>
  DECLARE_DELEGATE_OneParam(FOnStatusMessageEvent, const FString& InMessage);

  /// <summary>
  /// The callback type of console message from the web content.
  /// </summary>
  /// <param name="InMessage">The message.</param>
  /// <param name="InLevel">The level.</param>
  DECLARE_DELEGATE_TwoParams(FOnConsoleMessageEvent, const FString& InMessage, int32 InLevel);

  /// <summary>
  /// The callback type of loading progress changed.
  /// </summary>
  /// <param name="InProgress">Current progress.</param>
  DECLARE_DELEGATE_OneParam(FOnLoadingProgressChangedEvent, double InProgress);

  /// <summary>
  /// The callback type of built-in scheme URL access.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InQuery">The full URL.</param>
  DECLARE_DELEGATE_ThreeParams(FOnUrlRequestEvent,
                               const int64& InBrowserId,
                               const FCefFrameId& InFrameId,
                               const FString& InQuery);

  /// <summary>
  /// The callback type of new <see cref="UCefQuery"/> request.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InQueryId">The query ID.</param>
  /// <param name="InRequest">The query request.</param>
  DECLARE_DELEGATE_FourParams(FOnQueryRequestEvent,
                              const int64& InBrowserId,
                              const FCefFrameId& InFrameId,
                              const int64& InQueryId,
                              const FString& InRequest);

  /// <summary>
  /// The callback type of invoking method request from web content (JavaScript).
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InMethod">The method name.</param>
  /// <param name="InArguments">The arguments list.</param>
  DECLARE_DELEGATE_FourParams(FOnInvokeMethodEvent,
                              const int64& InBrowserId,
                              const FCefFrameId& InFrameId,
                              const FString& InMethod,
                              const TArray<TSharedPtr<FJsonValue>>& InArguments);

  /// <summary>
  /// The callback type of the result of the JavaScript executed with <see cref="executeJavascriptWithResult"/>
  /// returned.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InContext">The context.</param>
  /// <param name="InResult">The result.</param>
  DECLARE_DELEGATE_FourParams(FOnReportJavascriptResultEvent,
                              const int64& InBrowserId,
                              const FCefFrameId& InFrameId,
                              const FString& InContext,
                              const TSharedPtr<FJsonValue>& InResult);

  /// <summary>
  /// The callback type of the native browser window created event. This callback does not work for OSR mode.
  /// </summary>
  DECLARE_DELEGATE(FOnNativeBrowserCreatedEvent);

  /// <summary>
  /// The callback type when new browser is requested to be created.
  /// </summary>
  /// <param name="InSourceFrameId">The frame id which requests to create a new browser.</param>
  /// <param name="InUrl">The URL of the new browser.</param>
  /// <param name="InName">The name of the new browser.</param>
  /// <param name="InTargetDisposition">The target disposition of the new browser.</param>
  /// <param name="InRect">The rect of the new browser.</param>
  DECLARE_DELEGATE_FiveParams(FOnCreateNewBrowserEvent,
                              const FCefFrameId& InSourceFrameId,
                              const FString& InUrl,
                              const FString& InName,
                              const ECefWindowOpenDisposition& InTargetDisposition,
                              const FIntRect& InRect);
#pragma endregion

#pragma region Arguments & Properties
  /// <summary>
  /// Represents the construction arguments of SCefView.
  /// </summary>
  /// <param name=""></param>
  SLATE_BEGIN_ARGS(SCefView) {}

  /// <summary>
  /// The URL.
  /// </summary>
  SLATE_ARGUMENT(FString, Url)

  /// <summary>
  ///
  /// </summary>
  SLATE_ARGUMENT(bool, bEnableContextMenu);

  /// <summary>
  ///
  /// </summary>
  SLATE_ARGUMENT(bool, bEnableTransparentInputPassthrough);

  /// <summary>
  ///
  /// </summary>
  SLATE_ARGUMENT(bool, bAcceptDrops);

  /// <summary>
  ///
  /// </summary>
  SLATE_ARGUMENT(bool, bAllowDrag);

  /// <summary>
  /// The Settings.
  /// </summary>
  SLATE_ARGUMENT(FSlateCefViewSettings, Settings)

  /// <summary>
  /// The event handler of OnLoadStateChanged.
  /// </summary>
  SLATE_EVENT(FOnLoadStateChangedEvent, OnLoadStateChanged)

  /// <summary>
  /// The event handler of OnLoadStart.
  /// </summary>
  SLATE_EVENT(FOnLoadStartEvent, OnLoadStart)

  /// <summary>
  /// The event handler of OnLoadEnd.
  /// </summary>
  SLATE_EVENT(FOnLoadEndEvent, OnLoadEnd)

  /// <summary>
  /// The event handler of OnLoadError.
  /// </summary>
  SLATE_EVENT(FOnLoadErrorEvent, OnLoadError)

  /// <summary>
  /// The event handler of OnDraggableRegionChanged.
  /// </summary>
  SLATE_EVENT(FOnDraggableRegionChangedEvent, OnDraggableRegionChanged)

  /// <summary>
  /// The event handler of OnAddressChanged.
  /// </summary>
  SLATE_EVENT(FOnAddressChangedEvent, OnAddressChanged)

  /// <summary>
  /// The event handler of OnTitleChanged.
  /// </summary>
  SLATE_EVENT(FOnTitleChangedEvent, OnTitleChanged)

  /// <summary>
  /// The event handler of OnFaviconUrlChanged.
  /// </summary>
  SLATE_EVENT(FOnFaviconUrlChangedEvent, OnFaviconUrlChanged)

  /// <summary>
  /// The event handler of OnFullscreenModeChanged.
  /// </summary>
  SLATE_EVENT(FOnFullscreenModeChangedEvent, OnFullscreenModeChanged)

  /// <summary>
  /// The event handler of OnStatusMessage.
  /// </summary>
  SLATE_EVENT(FOnStatusMessageEvent, OnStatusMessage)

  /// <summary>
  /// The event handler of OnConsoleMessage.
  /// </summary>
  SLATE_EVENT(FOnConsoleMessageEvent, OnConsoleMessage)

  /// <summary>
  /// The event handler of OnLoadingProgressChanged.
  /// </summary>
  SLATE_EVENT(FOnLoadingProgressChangedEvent, OnLoadingProgressChanged)

  /// <summary>
  /// The event handler of OnUrlRequest.
  /// </summary>
  SLATE_EVENT(FOnUrlRequestEvent, OnUrlRequest)

  /// <summary>
  /// The event handler of OnQueryRequest.
  /// </summary>
  SLATE_EVENT(FOnQueryRequestEvent, OnQueryRequest)

  /// <summary>
  /// The event handler of OnInvokeMethod.
  /// </summary>
  SLATE_EVENT(FOnInvokeMethodEvent, OnInvokeMethod)

  /// <summary>
  /// The event handler of OnReportJavascriptResult.
  /// </summary>
  SLATE_EVENT(FOnReportJavascriptResultEvent, OnReportJavascriptResult)

  /// <summary>
  /// The event handler of OnNativeBrowserCreated.
  /// </summary>
  SLATE_EVENT(FOnNativeBrowserCreatedEvent, OnNativeBrowserCreated)

  /// <summary>
  ///
  /// </summary>
  SLATE_EVENT(FOnCreateNewBrowserEvent, OnCreateNewBrowser)

  //
  SLATE_END_ARGS()
#pragma endregion

#pragma region Constructors
  /// <summary>
  /// Default constructor for SCefView.
  /// </summary>
  SCefView();

  /// <summary>
  /// Destructor for SCefView.
  /// </summary>
  ~SCefView();

  /// <summary>
  /// Constructs the widget with the specified arguments.
  /// </summary>
  /// <param name="InArgs">The construction arguments.</param>
  void Construct(const FArguments& InArgs);
#pragma endregion

#pragma region Getters & Setters
  /// <summary>
  /// Sets the URL to be loaded in the browser.
  /// </summary>
  /// <param name="InUrl">The URL to load.</param>
  void SetUrl(const FString& InUrl);

  /// <summary>
  /// Gets the current URL loaded in the browser.
  /// </summary>
  /// <returns>The current URL.</returns>
  FString GetUrl() const;

  /// <summary>
  /// Enables or disables the context menu in the browser.
  /// </summary>
  /// <param name="bInEnableContextMenu">True to enable, false to disable.</param>
  void SetEnableContextMenu(bool bInEnableContextMenu);

  /// <summary>
  /// Checks if the context menu is enabled.
  /// </summary>
  /// <returns>True if enabled, false otherwise.</returns>
  bool IsContextMenuEnabled() const;

  /// <summary>
  /// Enables or disables transparent input passthrough.
  /// </summary>
  /// <param name="bInEnableTransparentInputPassthrough">True to pass input through transparent pixels.</param>
  void SetEnableTransparentInputPassthrough(bool bInEnableTransparentInputPassthrough);

  /// <summary>
  /// Checks if transparent input passthrough is enabled.
  /// </summary>
  /// <returns>True if enabled, false otherwise.</returns>
  bool IsTransparentInputPassthroughEnabled() const;

  /// <summary>
  /// Enables or disables accepting drag-and-drop operations.
  /// </summary>
  /// <param name="bInAcceptDrops">True to accept drops, false otherwise.</param>
  void SetAcceptDrops(bool bInAcceptDrops);

  /// <summary>
  /// Checks if drag-and-drop is accepted.
  /// </summary>
  /// <returns>True if accepted, false otherwise.</returns>
  bool IsAcceptDrops() const;

  /// <summary>
  /// Enables or disables allowing drag operations.
  /// </summary>
  /// <param name="bInAllowDrag">True to allow drag, false otherwise.</param>
  void SetAllowDrag(bool bInAllowDrag);

  /// <summary>
  /// Checks if drag operations are allowed.
  /// </summary>
  /// <returns>True if allowed, false otherwise.</returns>
  bool IsAllowDrag() const;
#pragma endregion

protected:
  /// <summary>
  /// Creates the native CEF browser instance with the specified settings.
  /// </summary>
  /// <param name="InCefViewSettings">The CEF browser settings.</param>
  void CreateNativeBrowser(const FSlateCefViewSettings& InCefViewSettings);

  /// <summary>
  /// Destroys the native CEF browser instance.
  /// </summary>
  void DestroyNativeBrowser();

#pragma region Methods
public:
  /// <summary>
  /// Adds a local folder as a web resource mapping.
  /// </summary>
  /// <param name="InFolderPath">Path to the local folder.</param>
  /// <param name="InTargetUrl">URL to map the folder to.</param>
  /// <param name="InPriority">Priority of the mapping (default: 0).</param>
  void AddLocalFolderResource(const FString& InFolderPath, const FString& InTargetUrl, int32 InPriority = 0);

  /// <summary>
  /// Adds an archive file (.zip) as a web resource mapping.
  /// </summary>
  /// <param name="InArchivePath">Path to the archive file.</param>
  /// <param name="InTargetUrl">URL to map the archive to.</param>
  /// <param name="InPassword">Password for the archive (default: empty).</param>
  /// <param name="InPriority">Priority of the mapping (default: 0).</param>
  void AddArchiveFileResource(const FString& InArchivePath,
                              const FString& InTargetUrl,
                              const FString& InPassword = "",
                              int32 InPriority = 0);

  /// <summary>
  /// Gets the unique browser ID.
  /// </summary>
  /// <returns>The browser ID.</returns>
  int64 GetBrowserId() const;

  /// <summary>
  /// Checks if the browser can navigate back in its history.
  /// </summary>
  /// <returns>True if it can go back, false otherwise.</returns>
  bool BrowserCanGoBack();

  /// <summary>
  /// Checks if the browser can navigate forward in its history.
  /// </summary>
  /// <returns>True if it can go forward, false otherwise.</returns>
  bool BrowserCanGoForward();

  /// <summary>
  /// Navigates the browser back in its history.
  /// </summary>
  void BrowserGoBack();

  /// <summary>
  /// Navigates the browser forward in its history.
  /// </summary>
  void BrowserGoForward();

  /// <summary>
  /// Checks if the browser is currently loading a page.
  /// </summary>
  /// <returns>True if loading, false otherwise.</returns>
  bool IsBrowserLoading();

  /// <summary>
  /// Reloads the current page in the browser.
  /// </summary>
  void BrowserReload();

  /// <summary>
  /// Stops the current page load in the browser.
  /// </summary>
  void BrowserStopLoad();

  /// <summary>
  /// Triggers a custom event for a specific frame in the browser.
  /// </summary>
  /// <param name="InName">Name of the event.</param>
  /// <param name="InArgs">Arguments to pass to the event.</param>
  /// <param name="InFrameId">Frame ID to trigger the event on.</param>
  /// <returns>True if the event was triggered successfully, false otherwise.</returns>
  bool TriggerEventForFrame(const FString& InName,
                            const TArray<TSharedPtr<FJsonValue>>& InArgs,
                            const FCefFrameId& InFrameId);

  /// <summary>
  /// Triggers a custom event for the main frame in the browser.
  /// </summary>
  /// <param name="InName">Name of the event.</param>
  /// <param name="InArgs">Arguments to pass to the event.</param>
  /// <returns>True if the event was triggered successfully, false otherwise.</returns>
  bool TriggerEventForMainFrame(const FString& InName, const TArray<TSharedPtr<FJsonValue>>& InArgs);

  /// <summary>
  /// Broadcasts a custom event to all frames in the browser.
  /// </summary>
  /// <param name="InName">Name of the event.</param>
  /// <param name="InArgs">Arguments to pass to the event.</param>
  /// <returns>True if the event was broadcast successfully, false otherwise.</returns>
  bool BroadcastEvent(const FString& InName, const TArray<TSharedPtr<FJsonValue>>& InArgs);

  /// <summary>
  /// Replies to a UCefQuery request from the browser.
  /// </summary>
  /// <param name="InQueryId">ID of the query to respond to.</param>
  /// <param name="bInIsSuccess">True if the query was successful.</param>
  /// <param name="InResponse">Response string.</param>
  /// <param name="InError">Error code, if any.</param>
  /// <returns>True if the response was sent successfully, false otherwise.</returns>
  bool ReplyUCefQuery(const int64 InQueryId, const bool bInIsSuccess, const FString& InResponse, const int32 InError);

  /// <summary>
  /// Executes JavaScript code in a specific frame.
  /// </summary>
  /// <param name="InFrameId">Frame ID to execute the code in.</param>
  /// <param name="InJavascriptCode">JavaScript code to execute.</param>
  /// <param name="InTargetUrl">URL to associate with the code.</param>
  /// <returns>True if the code was executed successfully, false otherwise.</returns>
  bool ExecuteJavascript(const FCefFrameId& InFrameId, const FString& InJavascriptCode, const FString& InTargetUrl);

  /// <summary>
  /// Executes JavaScript code in a specific frame and returns the result.
  /// </summary>
  /// <param name="InFrameId">Frame ID to execute the code in.</param>
  /// <param name="InJavascriptCode">JavaScript code to execute.</param>
  /// <param name="InTargetUrl">URL to associate with the code.</param>
  /// <param name="InExecuteContext">Context in which to execute the code.</param>
  /// <returns>True if the code was executed successfully, false otherwise.</returns>
  bool ExecuteJavascriptWithResult(const FCefFrameId& InFrameId,
                                   const FString& InJavascriptCode,
                                   const FString& InTargetUrl,
                                   const FString& InExecuteContext);

  /// <summary>
  /// Sets a browser preference.
  /// </summary>
  /// <param name="InPreferenceName">Name of the preference.</param>
  /// <param name="InPreferenceValue">Value to set.</param>
  /// <param name="OutError">Error message, if any.</param>
  /// <returns>True if the preference was set successfully, false otherwise.</returns>
  bool SetPreference(const FString& InPreferenceName, const FString& InPreferenceValue, FString& OutError);

  /// <summary>
  /// Checks if the browser's developer tools are open.
  /// </summary>
  /// <returns>True if open, false otherwise.</returns>
  bool HasDevTools();

  /// <summary>
  /// Opens the browser's developer tools dialog.
  /// </summary>
  void ShowDevTools();

  /// <summary>
  /// Closes the browser's developer tools dialog.
  /// </summary>
  void CloseDevTools();

#pragma endregion

#pragma region Events
protected:
  /// <summary>
  /// On load state changed event.
  /// </summary>
  FOnLoadStateChangedEvent OnLoadStateChanged;

  /// <summary>
  /// On load start event.
  /// </summary>
  FOnLoadStartEvent OnLoadStart;

  /// <summary>
  /// On load end event.
  /// </summary>
  FOnLoadEndEvent OnLoadEnd;

  /// <summary>
  /// On load error event.
  /// </summary>
  FOnLoadErrorEvent OnLoadError;

  /// <summary>
  /// On draggable region changed event.
  /// </summary>
  FOnDraggableRegionChangedEvent OnDraggableRegionChanged;

  /// <summary>
  /// On address changed event.
  /// </summary>
  FOnAddressChangedEvent OnAddressChanged;

  /// <summary>
  /// On title changed event.
  /// </summary>
  FOnTitleChangedEvent OnTitleChanged;

  /// <summary>
  /// On favicon URL changed event.
  /// </summary>
  FOnFaviconUrlChangedEvent OnFaviconUrlChanged;

  /// <summary>
  /// On fullscreen mode changed event.
  /// </summary>
  FOnFullscreenModeChangedEvent OnFullscreenModeChanged;

  /// <summary>
  /// On status message event.
  /// </summary>
  FOnStatusMessageEvent OnStatusMessage;

  /// <summary>
  /// On console message event.
  /// </summary>
  FOnConsoleMessageEvent OnConsoleMessage;

  /// <summary>
  /// On loading progress changed event.
  /// </summary>
  FOnLoadingProgressChangedEvent OnLoadingProgressChanged;

  /// <summary>
  /// On URL request event.
  /// </summary>
  FOnUrlRequestEvent OnUrlRequest;

  /// <summary>
  /// On query request event.
  /// </summary>
  FOnQueryRequestEvent OnQueryRequest;

  /// <summary>
  /// On invoke method event.
  /// </summary>
  FOnInvokeMethodEvent OnInvokeMethod;

  /// <summary>
  /// On report JavaScript result event.
  /// </summary>
  FOnReportJavascriptResultEvent OnReportJavascriptResult;

  /// <summary>
  /// On native browser created event.
  /// </summary>
  FOnNativeBrowserCreatedEvent OnNativeBrowserCreated;

  /// <summary>
  /// On new browser request event
  /// </summary>
  FOnCreateNewBrowserEvent OnCreateNewBrowser;
#pragma endregion

#pragma region Inner Methods
protected:
  /// <summary>
  /// Called when a new browser is created (e.g., via window.open).
  /// </summary>
  /// <param name="InSourceFrameId">ID of the source frame.</param>
  /// <param name="InTargetUrl">URL of the new browser.</param>
  /// <param name="InFrameName">Name of the new browser frame.</param>
  /// <param name="InTargetDisposition">Disposition of the new browser window.</param>
  /// <param name="InDesiredRect">Desired rectangle for the new browser window.</param>
  void OnNewBrowser(const FCefFrameId& InSourceFrameId,
                    const FString& InTargetUrl,
                    const FString& InFrameName,
                    const ECefWindowOpenDisposition& InTargetDisposition,
                    const FIntRect& InDesiredRect);

  /// <summary>
  /// Called before a pop-up browser is created (only for browser created by JavaScript).
  /// </summary>
  /// <param name="InSourceFrameId">Source frame ID.</param>
  /// <param name="InTargetUrl">Target URL.</param>
  /// <param name="InFrameName">Target frame name.</param>
  /// <param name="InTargetDisposition">Target window open method.</param>
  /// <param name="InDesiredRect">Rectangle for the popup.</param>
  /// <param name="InBrowserSettings">Settings for the popup browser.</param>
  /// <param name="bInDisableJavascriptAccess">Whether to disable JavaScript access.</param>
  /// <returns>True to cancel the popup, false to allow.</returns>
  bool OnNewPopup(const FCefFrameId& InSourceFrameId,
                  const FString& InTargetUrl,
                  FString& InFrameName,
                  ECefWindowOpenDisposition InTargetDisposition,
                  FIntRect& InDesiredRect,
                  FSlateCefViewSettings& InBrowserSettings,
                  bool& bInDisableJavascriptAccess);

  /// <summary>
  /// Called when a close request is received from the web content.
  /// </summary>
  /// <returns>True to allow the close, false to cancel.</returns>
  bool OnRequestCloseFromWeb();
#pragma endregion

#pragma region Overrides Parent
protected:
  /// <summary>
  /// Sets the visibility.
  /// </summary>
  /// <param name="InVisibility">The visibility.</param>
  void SetVisibility(TAttribute<EVisibility> InVisibility) override;

  /// <summary>
  /// Tick function.
  /// </summary>
  /// <param name="InAllottedGeometry">The allotted geometry.</param>
  /// <param name="InCurrentTime">The current time.</param>
  /// <param name="InDeltaTime">The delta time.</param>
  void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

  /// <summary>
  /// GetChildren function.
  /// </summary>
  /// <returns>The children.</returns>
  FChildren* GetChildren() override;

  /// <summary>
  /// OnArrangeChildren function.
  /// </summary>
  /// <param name="InAllottedGeometry">The allotted geometry.</param>
  /// <param name="InArrangedChildren">The arranged children.</param>
  void OnArrangeChildren(const FGeometry& InAllottedGeometry, FArrangedChildren& InArrangedChildren) const override;

  /// <summary>
  /// ComputeDesiredSize function.
  /// </summary>
  /// <param name="InLayoutScaleMultiplier">The layout scale multiplier.</param>
  /// <returns>The desired size.</returns>
  FVector2D ComputeDesiredSize(float InLayoutScaleMultiplier) const override;

  /// <summary>
  /// OnPaint function.
  /// </summary>
  /// <param name="InArgs">The paint arguments.</param>
  /// <param name="InAllottedGeometry">The allotted geometry.</param>
  /// <param name="InMyCullingRect">The my culling rectangle.</param>
  /// <param name="InOutDrawElements">The out draw elements.</param>
  /// <param name="InLayerId">The layer ID.</param>
  /// <param name="InWidgetStyle">The widget style.</param>
  /// <param name="bInParentEnabled">Whether the parent is enabled.</param>
  /// <returns>The layer ID.</returns>
  int32 OnPaint(const FPaintArgs& InArgs,
                const FGeometry& InAllottedGeometry,
                const FSlateRect& InMyCullingRect,
                FSlateWindowElementList& InOutDrawElements,
                int32 InLayerId,
                const FWidgetStyle& InWidgetStyle,
                bool bInParentEnabled) const override;

  /// <summary>
  /// OnMapCursor function.
  /// </summary>
  /// <param name="InCursorReply">The cursor reply.</param>
  /// <returns>The mapped cursor.</returns>
  TOptional<TSharedRef<SWidget>> OnMapCursor(const FCursorReply& InCursorReply) const;

  /// <summary>
  /// SupportsKeyboardFocus function.
  /// </summary>
  /// <returns>Whether the widget supports keyboard focus.</returns>
  bool SupportsKeyboardFocus() const override;

  /// <summary>
  /// OnFocusReceived function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InFocusEvent">The focus event.</param>
  /// <returns>The reply.</returns>
  FReply OnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

  /// <summary>
  /// OnFocusLost function.
  /// </summary>
  /// <param name="InFocusEvent">The focus event.</param>
  void OnFocusLost(const FFocusEvent& InFocusEvent) override;

  /// <summary>
  /// OnNavigation function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InNavigationEvent">The navigation event.</param>
  /// <returns>The navigation reply.</returns>
  FNavigationReply OnNavigation(const FGeometry& InGeometry, const FNavigationEvent& InNavigationEvent) override;

#pragma region Mouse Events
  /// <summary>
  /// OnMouseEnter function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InMouseEvent">The mouse event.</param>
  void OnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

  /// <summary>
  /// OnMouseLeave function.
  /// </summary>
  /// <param name="InMouseEvent">The mouse event.</param>
  void OnMouseLeave(const FPointerEvent& InMouseEvent) override;

  /// <summary>
  /// OnMouseMove function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InMouseEvent">The mouse event.</param>
  /// <returns>The reply.</returns>
  FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

  /// <summary>
  /// OnPreviewMouseButtonDown function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InMouseEvent">The mouse event.</param>
  /// <returns>The reply.</returns>
  FReply OnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

  /// <summary>
  /// OnMouseButtonDown function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InMouseEvent">The mouse event.</param>
  /// <returns>The reply.</returns>
  FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

  /// <summary>
  /// OnMouseButtonUp function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InMouseEvent">The mouse event.</param>
  /// <returns>The reply.</returns>
  FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

  /// <summary>
  /// OnMouseButtonDoubleClick function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InMouseEvent">The mouse event.</param>
  /// <returns>The reply.</returns>
  FReply OnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

  /// <summary>
  /// OnMouseWheel function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InMouseEvent">The mouse event.</param>
  /// <returns>The reply.</returns>
  FReply OnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
#pragma endregion

#pragma region Touch Events
  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InGestureEvent"></param>
  /// <returns></returns>
  FReply OnTouchGesture(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InTouchEvent"></param>
  /// <returns></returns>
  FReply OnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InTouchEvent"></param>
  /// <returns></returns>
  FReply OnTouchFirstMove(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InTouchEvent"></param>
  /// <returns></returns>
  FReply OnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InTouchEvent"></param>
  /// <returns></returns>
  FReply OnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InTouchEvent"></param>
  /// <returns></returns>
  FReply OnTouchForceChanged(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent) override;

#pragma endregion

#pragma region Keyboard Events
  /// <summary>
  /// OnPreviewKeyDown function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InKeyEvent">The key event.</param>
  /// <returns>The reply.</returns>
  FReply OnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

  /// <summary>
  /// OnKeyDown function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InKeyEvent">The key event.</param>
  /// <returns>The reply.</returns>
  FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

  /// <summary>
  /// OnKeyChar function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InCharacterEvent">The character event.</param>
  /// <returns>The reply.</returns>
  FReply OnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharacterEvent) override;

  /// <summary>
  /// OnKeyUp function.
  /// </summary>
  /// <param name="InGeometry">The geometry.</param>
  /// <param name="InKeyEvent">The key event.</param>
  /// <returns>The reply.</returns>
  FReply OnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InDragDropEvent"></param>
  void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InDragDropEvent"></param>
  /// <returns></returns>
  FReply OnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InDragDropEvent"></param>
  /// <returns></returns>
  FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="DragDropEvent"></param>
  void OnDragLeave(const FDragDropEvent& DragDropEvent) override;

  /// <summary>
  ///
  /// </summary>
  /// <param name="InGeometry"></param>
  /// <param name="InMouseEvent"></param>
  /// <returns></returns>
  FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
#pragma endregion

#pragma endregion
};
