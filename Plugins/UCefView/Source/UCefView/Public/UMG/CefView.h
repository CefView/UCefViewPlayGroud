//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file CefView.h
//! @brief Declares the UCefView class, a UMG widget that hosts a CEF browser view.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/Array.h>
#include <Containers/UnrealString.h>
#include <Delegates/DelegateCombinations.h>
#include <HAL/Platform.h>
#include <Math/IntRect.h>
#include <UObject/NameTypes.h>
// CoreUObject/Public/
#include <UObject/ObjectMacros.h>
// UMG/Public/
#include <Components/Widget.h>
#include <Blueprint/UserWidget.h>
#pragma endregion

#pragma region <Project Public Headers>
#include <CefViewTypes.h>
#include <CefContext.h>
#include <CefViewEvent.h>
#include <CefViewQuery.h>
#include <UMG/CefViewSettings.h>
#include <Slate/SCefView.h>
#pragma endregion

#pragma region "Generated Header"
#include "CefView.generated.h"
#pragma endregion

/// <summary>
/// UCefView is a UMG widget that embeds a Chromium Embedded Framework (CEF) browser view within Unreal Engine UI.
/// It provides a rich set of browser features, event hooks, and resource mapping capabilities, allowing seamless
/// integration of web content into Unreal Engine applications. The widget supports navigation, JavaScript execution,
/// event broadcasting, and advanced customization through settings and resource mappings. It is suitable for both
/// in-game and editor use, and exposes a comprehensive set of Blueprint-callable methods and events for interaction.
/// </summary>
UCLASS(BlueprintType)
class UCEFVIEW_API UCefView : public UWidget
{
  GENERATED_BODY()

public:
  /// <summary>
  /// The main frame identity, representing the primary document frame in the browser.
  /// Used for targeting main-frame-specific operations and events.
  /// </summary>
  static const FCefFrameId MainFrameID;

  /// <summary>
  /// The identifier representing all frames in the browser.
  /// Used for broadcasting events or actions to every frame.
  /// </summary>
  static const FCefFrameId AllFrameID;

#pragma region Properties
private:
  /// <summary>
  /// The initial URL to be loaded in the CEF browser when the widget is created.
  /// Can be changed at runtime to navigate to a different page.
  /// </summary>
  UPROPERTY(                  //
    BlueprintReadWrite,       //
    BlueprintSetter = SetUrl, //
    BlueprintGetter = GetUrl, //
    EditInstanceOnly,         //
    Category = "CefView",     //
    meta = (AllowPrivateAccess = "true")
  )
  FString Url;

public:
  /// <summary>
  /// Sets the target URL and navigates the live browser if it already exists.
  /// </summary>
  /// <param name="InUrl">The URL to load.</param>
  UFUNCTION(BlueprintSetter)
  void SetUrl(const FString& InUrl);

  /// <summary>
  /// Gets the currently configured target URL.
  /// </summary>
  /// <returns>The current URL.</returns>
  UFUNCTION(BlueprintGetter)
  FString GetUrl() const;

private:
  /// <summary>
  /// Enables or disables the context menu in the CEF browser.
  /// If true, right-click context menus are shown; if false, they are suppressed.
  /// Default: true
  /// </summary>
  UPROPERTY(                                //
    BlueprintReadWrite,                     //
    BlueprintSetter = SetEnableContextMenu, //
    BlueprintGetter = GetEnableContextMenu, //
    EditInstanceOnly,                       //
    Category = "CefView",                   //
    meta = (AllowPrivateAccess = "true")
  )
  bool bEnableContextMenu = true;

public:
  /// <summary>
  /// Enables or disables the browser context menu.
  /// </summary>
  /// <param name="bInEnableContextMenu">True to enable the context menu; false to suppress it.</param>
  UFUNCTION(BlueprintSetter)
  void SetEnableContextMenu(bool bInEnableContextMenu);

  /// <summary>
  /// Gets whether the browser context menu is enabled.
  /// </summary>
  /// <returns>True if the context menu is enabled; otherwise, false.</returns>
  UFUNCTION(BlueprintGetter)
  bool GetEnableContextMenu() const;

private:
  /// <summary>
  /// Enables or disables input passthrough on transparent browser pixels.
  /// If true, mouse/touch/drag input over transparent rendered pixels is not consumed by the CEF view.
  /// Default: false
  /// </summary>
  UPROPERTY(                                                //
    BlueprintReadWrite,                                     //
    BlueprintSetter = SetEnableTransparentInputPassthrough, //
    BlueprintGetter = GetEnableTransparentInputPassthrough, //
    EditInstanceOnly,                                      //
    Category = "CefView",                                  //
    meta = (AllowPrivateAccess = "true")
  )
  bool bEnableTransparentInputPassthrough = false;

public:
  /// <summary>
  /// Enables or disables input passthrough for transparent rendered pixels.
  /// </summary>
  /// <param name="bInEnableTransparentInputPassthrough">True to pass input through transparent pixels.</param>
  UFUNCTION(BlueprintSetter)
  void SetEnableTransparentInputPassthrough(bool bInEnableTransparentInputPassthrough);

  /// <summary>
  /// Gets whether transparent input passthrough is enabled.
  /// </summary>
  /// <returns>True if transparent input passthrough is enabled; otherwise, false.</returns>
  UFUNCTION(BlueprintGetter)
  bool GetEnableTransparentInputPassthrough() const;

private:
  /// <summary>
  /// Enables or disables accepting drag-and-drop operations from external sources (e.g., files from OS).
  /// If true, the browser can accept drops; if false, drops are ignored.
  /// Default: false
  /// </summary>
  UPROPERTY(                          //
    BlueprintReadWrite,               //
    BlueprintSetter = SetAcceptDrops, //
    BlueprintGetter = GetAcceptDrops, //
    EditInstanceOnly,                 //
    Category = "CefView",            //
    meta = (AllowPrivateAccess = "true")
  )
  bool bAcceptDrops = true;

public:
  /// <summary>
  /// Enables or disables accepting drag-and-drop data from external sources.
  /// </summary>
  /// <param name="bInAcceptDrops">True to accept drops; otherwise, false.</param>
  UFUNCTION(BlueprintSetter)
  void SetAcceptDrops(bool bInAcceptDrops);

  /// <summary>
  /// Gets whether external drag-and-drop input is accepted.
  /// </summary>
  /// <returns>True if drops are accepted; otherwise, false.</returns>
  UFUNCTION(BlueprintGetter)
  bool GetAcceptDrops() const;

private:
  /// <summary>
  /// Enables or disables allowing the browser content to be dragged (initiating drag operations).
  /// If true, users can drag content from the browser; if false, dragging is disabled.
  /// Default: false
  /// </summary>
  UPROPERTY(                        //
    BlueprintReadWrite,             //
    BlueprintSetter = SetAllowDrag, //
    BlueprintGetter = GetAllowDrag, //
    EditInstanceOnly,               //
    Category = "CefView",          //
    meta = (AllowPrivateAccess = "true")
  )
  bool bAllowDrag = true;

public:
  /// <summary>
  /// Enables or disables drag operations initiated from browser content.
  /// </summary>
  /// <param name="bInAllowDrag">True to allow dragging from browser content; otherwise, false.</param>
  UFUNCTION(BlueprintSetter)
  void SetAllowDrag(bool bInAllowDrag);

  /// <summary>
  /// Gets whether browser content can initiate drag operations.
  /// </summary>
  /// <returns>True if drag operations are allowed; otherwise, false.</returns>
  UFUNCTION(BlueprintGetter)
  bool GetAllowDrag() const;

  /// <summary>
  /// Mappings for local folders to be used as web resources.
  /// Each mapping allows content in the specified folder to be accessed via a virtual URL in the browser.
  /// </summary>
  UPROPERTY(             //
    BlueprintReadOnly,   //
    EditInstanceOnly,    //
    Category = "CefView" //
  )
  TArray<FLocalFolderResourceMapping> LocalFolderResourceMapping;

  /// <summary>
  /// Mappings for archive files (e.g., .zip) to be used as web resources.
  /// Each mapping allows content in the specified archive to be accessed via a virtual URL in the browser.
  /// </summary>
  UPROPERTY(             //
    BlueprintReadOnly,   //
    EditInstanceOnly,    //
    Category = "CefView" //
  )
  TArray<FArchiveFileResourceMapping> ArchiveFileResourceMapping;

  /// <summary>
  /// Settings for the CEF view, including browser features, font preferences, and other options.
  /// These settings are applied when the browser is created and cannot be changed at runtime.
  /// </summary>
  UPROPERTY(             //
    BlueprintReadOnly,   //
    EditInstanceOnly,    //
    Category = "CefView" //
  )
  FCefViewSettings Settings;

#pragma endregion

#pragma region Constructor
public:
  /// <summary>
  /// Default constructor. Initializes the UCefView widget and its properties.
  /// </summary>
  UCefView();

  /// <summary>
  /// Destructor. Cleans up resources associated with the CEF browser view.
  /// </summary>
  virtual ~UCefView();
#pragma endregion

#pragma region Overrides
protected:
  // SWidget interface
  TSharedPtr<SCefView> SlateCefView;

  /// <summary>
  /// Rebuilds the underlying Slate widget for this UMG widget.
  /// Called by the engine when the widget needs to be constructed or updated.
  /// </summary>
  /// <returns>A shared reference to the constructed Slate widget.</returns>
  virtual TSharedRef<SWidget> RebuildWidget() override;

public:
  /// <summary>
  /// Synchronizes UPROPERTY values with the underlying Slate widget.
  /// Called automatically by the engine when properties are changed in the editor or at runtime.
  /// </summary>
  virtual void SynchronizeProperties() override;

  /// <summary>
  /// Releases resources held by the Slate widget, optionally releasing child widgets as well.
  /// Called when the UMG widget is destroyed or removed from the UI hierarchy.
  /// </summary>
  /// <param name="bInReleaseChildren">If true, releases child widgets as well.</param>
  virtual void ReleaseSlateResources(bool bInReleaseChildren) override;

#if WITH_EDITOR
  /// <summary>
  /// Gets the category name for this widget in the UMG editor palette.
  /// </summary>
  /// <returns>The localized category name.</returns>
  virtual const FText GetPaletteCategory() override;
#endif
#pragma endregion

#pragma region Methods
public:
  /// <summary>
  /// Adds a URL mapping for a local web resource directory, making its contents accessible via a virtual URL.
  /// This is useful for serving local HTML, JS, or other assets to the browser.
  /// </summary>
  /// <param name="InFolderPath">The absolute or relative path to the local resource directory.</param>
  /// <param name="InTargetUrl">The virtual URL to map to the directory (e.g., "http://local/").</param>
  /// <param name="InPriority">The priority of the mapping. Higher values take precedence. Default is 0.</param>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void AddLocalFolderResource(const FString& InFolderPath, const FString& InTargetUrl, int32 InPriority = 0);

  /// <summary>
  /// Adds a URL mapping for a local archive (.zip) file, making its contents accessible via a virtual URL.
  /// This is useful for serving packaged web assets to the browser.
  /// </summary>
  /// <param name="InArchivePath">The absolute or relative path to the local archive file.</param>
  /// <param name="InTargetUrl">The virtual URL to map to the archive (e.g., "http://archive/").</param>
  /// <param name="InPassword">The password required to access the archive, if any. Default is empty.</param>
  /// <param name="InPriority">The priority of the mapping. Higher values take precedence. Default is 0.</param>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void AddArchiveFileResource(const FString& InArchivePath,
                              const FString& InTargetUrl,
                              const FString& InPassword = "",
                              int32 InPriority = 0);

  /// <summary>
  /// Gets the unique browser ID for this CEF view instance.
  /// </summary>
  /// <returns>The browser ID as a 64-bit integer.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  int64 GetBrowserId();

  /// <summary>
  /// Navigates the browser to the specified URL.
  /// </summary>
  /// <param name="InTargetUrl">The URL to navigate to.</param>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void NavigateToUrl(const FString& InTargetUrl);

  /// <summary>
  /// Checks whether the browser can navigate back in its history.
  /// </summary>
  /// <returns>True if the browser can go back; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool BrowserCanGoBack();

  /// <summary>
  /// Checks whether the browser can navigate forward in its history.
  /// </summary>
  /// <returns>True if the browser can go forward; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool BrowserCanGoForward();

  /// <summary>
  /// Navigates the browser back to the previous page in its history, if possible.
  /// </summary>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void BrowserGoBack();

  /// <summary>
  /// Navigates the browser forward to the next page in its history, if possible.
  /// </summary>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void BrowserGoForward();

  /// <summary>
  /// Checks whether the browser is currently loading a page or resource.
  /// </summary>
  /// <returns>True if the browser is loading; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool IsBrowserLoading();

  /// <summary>
  /// Reloads the current page in the browser.
  /// </summary>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void BrowserReload();

  /// <summary>
  /// Stops the current page load operation in the browser.
  /// </summary>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void BrowserStopLoad();

  /// <summary>
  /// Triggers a custom event for a specific frame in the CEF view.
  /// Allows sending user-defined events to the browser for advanced interaction.
  /// </summary>
  /// <param name="InCefViewEvent">The event object to trigger.</param>
  /// <param name="InFrameId">The ID of the frame to trigger the event on.</param>
  /// <returns>True if the event was successfully triggered; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool TriggerEventForFrame(const UCefViewEvent* InCefViewEvent, const FCefFrameId& InFrameId);

  /// <summary>
  /// Triggers a custom event for the main frame in the CEF view.
  /// </summary>
  /// <param name="InCefViewEvent">The event object to trigger.</param>
  /// <returns>True if the event was successfully triggered; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool TriggerEventForMainFrame(const UCefViewEvent* InCefViewEvent);

  /// <summary>
  /// Broadcasts a custom event to all frames in the CEF view.
  /// </summary>
  /// <param name="InCefViewEvent">The event object to broadcast.</param>
  /// <returns>True if the event was successfully broadcast; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool BroadcastEvent(const UCefViewEvent* InCefViewEvent);

  /// <summary>
  /// Replies to a CEF query with the provided result.
  /// Used for asynchronous communication between JavaScript and native code.
  /// </summary>
  /// <param name="InCefQuery">The CEF query object to respond to.</param>
  /// <returns>True if the query was successfully responded to; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool ReplyUCefQuery(const UCefViewQuery* InCefQuery);

  /// <summary>
  /// Executes JavaScript code in a specific frame of the CEF view.
  /// </summary>
  /// <param name="InFrameId">The ID of the frame in which to execute the JavaScript.</param>
  /// <param name="InJavascriptCode">The JavaScript code to execute.</param>
  /// <param name="InTargetUrl">The URL to associate with the script (used for debugging and stack traces).</param>
  /// <returns>True if the JavaScript was successfully executed; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool ExecuteJavascript(const FCefFrameId& InFrameId, const FString& InJavascriptCode, const FString& InTargetUrl);

  /// <summary>
  /// Executes JavaScript code in a specific frame and returns the result asynchronously.
  /// </summary>
  /// <param name="InFrameId">The ID of the frame in which to execute the JavaScript.</param>
  /// <param name="InJavascriptCode">The JavaScript code to execute.</param>
  /// <param name="InTargetUrl">The URL to associate with the script (used for debugging and stack traces).</param>
  /// <param name="InExecuteContext">The context in which the script is executed (e.g., "default", "isolated").</param>
  /// <returns>True if the JavaScript was successfully executed; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool ExecuteJavascriptWithResult(const FCefFrameId& InFrameId,
                                   const FString& InJavascriptCode,
                                   const FString& InTargetUrl,
                                   const FString& InExecuteContext);

  /// <summary>
  /// Sets a browser preference to a specified value.
  /// Preferences control browser behavior such as cache, cookies, and rendering options.
  /// </summary>
  /// <param name="InPreferenceName">The name of the preference to set (e.g.,
  /// "webkit.webprefs.javascript_enabled").</param> <param name="InPreferenceValue">The value to set the preference to
  /// (as a string).</param> <param name="InError">An output parameter that will contain an error message if the
  /// preference could not be set.</param> <returns>True if the preference was successfully set; otherwise,
  /// false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool SetPreference(const FString& InPreferenceName, const FString& InPreferenceValue, FString& InError);

  /// <summary>
  /// Detects whether the browser currently has a DevTools window open.
  /// </summary>
  /// <returns>True if DevTools is open; otherwise, false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool HasDevTools();

  /// <summary>
  /// Opens the DevTools dialog for the browser, allowing inspection and debugging of web content.
  /// </summary>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void ShowDevTools();

  /// <summary>
  /// Closes the DevTools dialog if it is currently open.
  /// </summary>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void CloseDevTools();

#pragma endregion

#pragma region Events
public:
  DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLoadStateChangedEvent,
                                                const int64&,
                                                InBrowserId,
                                                bool,
                                                bInIsLoading,
                                                bool,
                                                bInCanGoBack,
                                                bool,
                                                bInCanGoForward);
  /// <summary>
  /// Event triggered when the browser's loading state changes (e.g., starts or finishes loading).
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="bInIsLoading">True if the browser is currently loading; otherwise, false.</param>
  /// <param name="bInCanGoBack">True if the browser can navigate back; otherwise, false.</param>
  /// <param name="bInCanGoForward">True if the browser can navigate forward; otherwise, false.</param>
  UPROPERTY(BlueprintAssignable)
  FOnLoadStateChangedEvent OnLoadStateChanged;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLoadStartEvent,
                                                const int64&,
                                                InBrowserId,
                                                const FCefFrameId&,
                                                InFrameId,
                                                bool,
                                                bInIsMainFrame,
                                                int,
                                                InTransitionType);
  /// <summary>
  /// Event triggered when the browser starts loading a new document in any frame.
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="InFrameId">The frame ID where loading started.</param>
  /// <param name="bInIsMainFrame">True if this is the main frame; otherwise, false.</param>
  /// <param name="InTransitionType">The transition type (navigation reason).</param>
  UPROPERTY(BlueprintAssignable)
  FOnLoadStartEvent OnLoadStart;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLoadEndEvent,
                                                const int64&,
                                                InBrowserId,
                                                const FCefFrameId&,
                                                InFrameId,
                                                bool,
                                                bInIsMainFrame,
                                                int,
                                                InHttpStatusCode);
  /// <summary>
  /// Event triggered when the browser finishes loading a document in any frame.
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="InFrameId">The frame ID where loading ended.</param>
  /// <param name="bInIsMainFrame">True if this is the main frame; otherwise, false.</param>
  /// <param name="InHttpStatusCode">The HTTP status code of the loaded document.</param>
  UPROPERTY(BlueprintAssignable)
  FOnLoadEndEvent OnLoadEnd;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnLoadErrorEvent,
                                               const int64&,
                                               InBrowserId,
                                               const FCefFrameId&,
                                               InFrameId,
                                               bool,
                                               bInIsMainFrame,
                                               int,
                                               InErrorCode,
                                               const FString&,
                                               InErrorMsg,
                                               const FString&,
                                               InFailedUrl);
  /// <summary>
  /// Event triggered when the browser fails to load a document due to an error.
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="InFrameId">The frame ID where the error occurred.</param>
  /// <param name="bInIsMainFrame">True if this is the main frame; otherwise, false.</param>
  /// <param name="InErrorCode">The error code (see CEF error codes).</param>
  /// <param name="InErrorMsg">A descriptive error message.</param>
  /// <param name="InFailedUrl">The URL that failed to load.</param>
  UPROPERTY(BlueprintAssignable)
  FOnLoadErrorEvent OnLoadError;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDraggableRegionChangedEvent,
                                               const FVector4&,
                                               InDraggableRegion,
                                               const FVector4&,
                                               InNonDraggableRegion);
  /// <summary>
  /// Event triggered when the draggable or non-draggable regions of the browser change.
  /// Used for implementing custom window dragging in frameless windows.
  /// </summary>
  /// <param name="InDraggableRegion">The new draggable region (as a vector or rectangle).</param>
  /// <param name="InNonDraggableRegion">The new non-draggable region.</param>
  UPROPERTY(BlueprintAssignable)
  FOnDraggableRegionChangedEvent OnDraggableRegionChanged;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddressChangedEvent,
                                               const FCefFrameId&,
                                               InFrameId,
                                               const FString&,
                                               InNewAddress);
  /// <summary>
  /// Event triggered when the address (URL) of a frame changes.
  /// </summary>
  /// <param name="InFrameId">The frame ID whose address changed.</param>
  /// <param name="InNewAddress">The new address (URL).</param>
  UPROPERTY(BlueprintAssignable)
  FOnAddressChangedEvent OnAddressChanged;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTitleChangedEvent, const FString&, InTitle);
  /// <summary>
  /// Event triggered when the document title changes.
  /// </summary>
  /// <param name="InTitle">The new document title.</param>
  UPROPERTY(BlueprintAssignable)
  FOnTitleChangedEvent OnTitleChanged;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFaviconUrlChangedEvent, const TArray<FString>&, InUrls);
  /// <summary>
  /// Event triggered when the favicon URLs for the current page change.
  /// </summary>
  /// <param name="InUrls">The new list of favicon URLs.</param>
  UPROPERTY(BlueprintAssignable)
  FOnFaviconUrlChangedEvent OnFaviconUrlChanged;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFullscreenModeChangedEvent, bool, bInFullscreen);
  /// <summary>
  /// Event triggered when the browser enters or exits fullscreen mode.
  /// </summary>
  /// <param name="bInFullscreen">True if the browser is now in fullscreen mode; otherwise, false.</param>
  UPROPERTY(BlueprintAssignable)
  FOnFullscreenModeChangedEvent OnFullscreenModeChanged;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusMessageEvent, const FString&, InMessage);
  /// <summary>
  /// Event triggered when the browser's status message changes (e.g., link hover, loading status).
  /// </summary>
  /// <param name="InMessage">The new status message.</param>
  UPROPERTY(BlueprintAssignable)
  FOnStatusMessageEvent OnStatusMessage;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConsoleMessageEvent, const FString&, InMessage, int32, InLevel);
  /// <summary>
  /// Event triggered when a console message is emitted from web content (e.g., via console.log).
  /// </summary>
  /// <param name="InMessage">The console message text.</param>
  /// <param name="InLevel">The log level (e.g., info, warning, error).</param>
  UPROPERTY(BlueprintAssignable)
  FOnConsoleMessageEvent OnConsoleMessage;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingProgressChangedEvent, double, InProgress);
  /// <summary>
  /// Event triggered when the loading progress of the current page changes.
  /// </summary>
  /// <param name="InProgress">The current loading progress (0.0 to 1.0).</param>
  UPROPERTY(BlueprintAssignable)
  FOnLoadingProgressChangedEvent OnLoadingProgressChanged;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUrlRequestEvent,
                                                 const int64&,
                                                 InBrowserId,
                                                 const FCefFrameId&,
                                                 InFrameId,
                                                 const FString&,
                                                 InRequestUrl);
  /// <summary>
  /// Event triggered when a built-in scheme URL is accessed by the browser.
  /// Useful for handling custom resource requests.
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="InFrameId">The frame ID making the request.</param>
  /// <param name="InRequestUrl">The full requested URL.</param>
  UPROPERTY(BlueprintAssignable)
  FOnUrlRequestEvent OnUrlRequest;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQueryRequestEvent,
                                                 const int64&,
                                                 InBrowserId,
                                                 const FCefFrameId&,
                                                 InFrameId,
                                                 UCefViewQuery*,
                                                 InQuery);
  /// <summary>
  /// Event triggered when a new UCefQuery request is received from web content.
  /// Used for asynchronous communication between JavaScript and native code.
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="InFrameId">The frame ID making the query.</param>
  /// <param name="InQuery">The query request object.</param>
  UPROPERTY(BlueprintAssignable)
  FOnQueryRequestEvent OnQueryRequest;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnInvokeMethodEvent,
                                                const int64&,
                                                InBrowserId,
                                                const FCefFrameId&,
                                                InFrameId,
                                                const FString&,
                                                InMethod,
                                                const FString&,
                                                InArguments);
  /// <summary>
  /// Event triggered when a method is invoked from web content (JavaScript) via the bridge object.
  /// Allows native code to handle custom method calls from JavaScript.
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="InFrameId">The frame ID making the call.</param>
  /// <param name="InMethod">The name of the method being invoked.</param>
  /// <param name="InArguments">The arguments list as a JSON string.</param>
  UPROPERTY(BlueprintAssignable)
  FOnInvokeMethodEvent OnInvokeMethod;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnReportJavascriptResultEvent,
                                                const int64&,
                                                InBrowserId,
                                                const FCefFrameId&,
                                                InFrameId,
                                                const FString&,
                                                InContext,
                                                const FString&,
                                                InResult);
  /// <summary>
  /// Event triggered when the result of a JavaScript execution (via ExecuteJavascriptWithResult) is returned.
  /// </summary>
  /// <param name="InBrowserId">The unique browser ID.</param>
  /// <param name="InFrameId">The frame ID where the script was executed.</param>
  /// <param name="InContext">The execution context identifier.</param>
  /// <param name="InResult">The result of the JavaScript execution as a string.</param>
  UPROPERTY(BlueprintAssignable)
  FOnReportJavascriptResultEvent OnReportJavascriptResult;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNativeBrowserCreatedEvent);
  /// <summary>
  /// Event triggered when the native browser window is created.
  /// Note: This event does not fire in OSR (Off-Screen Rendering) mode.
  /// </summary>
  UPROPERTY(BlueprintAssignable)
  FOnNativeBrowserCreatedEvent OnNativeBrowserCreated;

  DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnCreateNewBrowserEvent,
                                                const FCefFrameId&,
                                                InSourceFrameId,
                                                const FString&,
                                                InUrl,
                                                const FString&,
                                                InName,
                                                const ECefWindowOpenDisposition&,
                                                InTargetDisposition,
                                                const FVector4&,
                                                InRect);
  /// <summary>
  /// The callback type when new browser is requested to be created.
  /// </summary>
  /// <param name="InSourceFrameId">The frame id which requests to create a new browser.</param>
  /// <param name="InUrl">The URL of the new browser.</param>
  /// <param name="InName">The name of the new browser.</param>
  /// <param name="InTargetDisposition">The target disposition of the new browser.</param>
  /// <param name="InRect">The rect of the new browser.</param>
  UPROPERTY(BlueprintAssignable)
  FOnCreateNewBrowserEvent OnCreateNewBrowser;

#pragma endregion

protected:
  /// <summary>
  /// Called before a new browser is created (for browsers created by non-JavaScript means).
  /// Allows customization of the new browser's properties and window.
  /// </summary>
  /// <param name="InSourceFrameId">The source frame ID initiating the new browser.</param>
  /// <param name="InUrl">The target URL to be loaded in the new browser.</param>
  /// <param name="InName">The target window name.</param>
  /// <param name="InTargetDisposition">
  /// The method by which the window should be opened (e.g., new tab, new window).
  /// </param>
  /// <param name="InRect">The rectangle specifying the popup window's position and size.</param>
  void OnNewBrowser(const FCefFrameId& InSourceFrameId,
                    const FString& InUrl,
                    const FString& InName,
                    ECefWindowOpenDisposition InTargetDisposition,
                    FIntRect& InRect);

  /// <summary>
  /// Called before a pop-up browser is created (for browsers created by JavaScript).
  /// Allows customization or cancellation of the popup.
  /// </summary>
  /// <param name="InFrameId">The source frame ID.</param>
  /// <param name="InTargetUrl">The target URL for the popup.</param>
  /// <param name="InTargetFrameName">The target frame name (modifiable).</param>
  /// <param name="InTargetDisposition">The method by which the window should be opened.</param>
  /// <param name="InRect">The rectangle specifying the popup window's position and size.</param>
  /// <param name="InSettings">Settings to be applied to the popup browser.</param>
  /// <param name="bInDisableJavascriptAccess">Set to true to disable JavaScript access in the popup.</param>
  /// <returns>True to cancel the popup; false to allow it.</returns>
  bool OnNewPopup(const FCefFrameId& InFrameId,
                  const FString& InTargetUrl,
                  FString& InTargetFrameName,
                  ECefWindowOpenDisposition InTargetDisposition,
                  FIntRect& InRect,
                  FSlateCefViewSettings& InSettings,
                  bool& bInDisableJavascriptAccess);

  /// <summary>
  /// Called when a close request is received from the web content (e.g., window.close()).
  /// </summary>
  /// <returns>True to allow the browser to close; false to cancel the close operation.</returns>
  bool OnRequestCloseFromWeb();

#pragma region Slate Event Handlers
protected:
  /// <summary>
  /// Handles the load state changed event from the underlying Slate CEF view.
  /// Updates internal state and broadcasts the OnLoadStateChanged event.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="bInIsLoading">True if loading; otherwise, false.</param>
  /// <param name="bInCanGoBack">True if can go back; otherwise, false.</param>
  /// <param name="bInCanGoForward">True if can go forward; otherwise, false.</param>
  void OnSlateLoadStateChangedEvent(const int64& InBrowserId,
                                    bool bInIsLoading,
                                    bool bInCanGoBack,
                                    bool bInCanGoForward);

  /// <summary>
  /// Handles the load start event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="bInIsMainFrame">True if main frame; otherwise, false.</param>
  /// <param name="InTransitionType">The navigation transition type.</param>
  void OnSlateLoadStartEvent(const int64& InBrowserId,
                             const FCefFrameId& InFrameId,
                             bool bInIsMainFrame,
                             int InTransitionType);

  /// <summary>
  /// Handles the load end event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="bInIsMainFrame">True if main frame; otherwise, false.</param>
  /// <param name="InHttpStatusCode">The HTTP status code.</param>
  void OnSlateLoadEndEvent(const int64& InBrowserId,
                           const FCefFrameId& InFrameId,
                           bool bInIsMainFrame,
                           int InHttpStatusCode);

  /// <summary>
  /// Handles the load error event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="bInIsMainFrame">True if main frame; otherwise, false.</param>
  /// <param name="InErrorCode">The error code.</param>
  /// <param name="InErrorMsg">The error message.</param>
  /// <param name="InFailedUrl">The URL that failed to load.</param>
  /// <param name="bInHandled">Set to true if the error was handled; otherwise, false.</param>
  void OnSlateLoadErrorEvent(const int64& InBrowserId,
                             const FCefFrameId& InFrameId,
                             bool bInIsMainFrame,
                             int InErrorCode,
                             const FString& InErrorMsg,
                             const FString& InFailedUrl,
                             bool& bInHandled);

  /// <summary>
  /// Handles the draggable region changed event from the underlying Slate CEF view.
  /// Used for updating window drag regions in custom window chrome scenarios.
  /// </summary>
  /// <param name="InDraggableRegion">The new draggable region.</param>
  /// <param name="InNonDraggableRegion">The new non-draggable region.</param>
  void OnSlateDraggableRegionChangedEvent(const FVector4& InDraggableRegion, const FVector4& InNonDraggableRegion);

  /// <summary>
  /// Handles the address changed event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InFrameId">The frame ID whose address changed.</param>
  /// <param name="InNewAddress">The new address (URL).</param>
  void OnSlateAddressChangedEvent(const FCefFrameId& InFrameId, const FString& InNewAddress);

  /// <summary>
  /// Handles the title changed event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InTitle">The new document title.</param>
  void OnSlateTitleChangedEvent(const FString& InTitle);

  /// <summary>
  /// Handles the favicon URL changed event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InUrls">The new favicon URLs.</param>
  void OnSlateFaviconUrlChangedEvent(const TArray<FString>& InUrls);

  /// <summary>
  /// Handles the fullscreen mode changed event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="bInFullscreen">True if fullscreen; otherwise, false.</param>
  void OnSlateFullscreenModeChangedEvent(bool bInFullscreen);

  /// <summary>
  /// Handles the status message event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InMessage">The status message.</param>
  void OnSlateStatusMessageEvent(const FString& InMessage);

  /// <summary>
  /// Handles the console message event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InMessage">The console message.</param>
  /// <param name="InLevel">The log level.</param>
  void OnSlateConsoleMessageEvent(const FString& InMessage, int32 InLevel);

  /// <summary>
  /// Handles the loading progress changed event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InProgress">The loading progress (0.0 to 1.0).</param>
  void OnSlateLoadingProgressChangedEvent(double InProgress);

  /// <summary>
  /// Handles the URL request event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InRequestUrl">The requested URL.</param>
  void OnSlateUrlRequestEvent(const int64& InBrowserId, const FCefFrameId& InFrameId, const FString& InRequestUrl);

  /// <summary>
  /// Handles the query request event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InQueryId">The query ID.</param>
  /// <param name="InRequest">The query request string.</param>
  void OnSlateQueryRequestEvent(const int64& InBrowserId,
                                const FCefFrameId& InFrameId,
                                const int64& InQueryId,
                                const FString& InRequest);

  /// <summary>
  /// Handles the invoke method event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InMethod">The method name to invoke.</param>
  /// <param name="InArguments">The arguments as a JSON value array.</param>
  void OnSlateInvokeMethodEvent(const int64& InBrowserId,
                                const FCefFrameId& InFrameId,
                                const FString& InMethod,
                                const TArray<TSharedPtr<FJsonValue>>& InArguments);

  /// <summary>
  /// Handles the report JavaScript result event from the underlying Slate CEF view.
  /// </summary>
  /// <param name="InBrowserId">The browser ID.</param>
  /// <param name="InFrameId">The frame ID.</param>
  /// <param name="InContext">The JavaScript execution context.</param>
  /// <param name="InResult">The result as a JSON value.</param>
  void OnSlateReportJavascriptResultEvent(const int64& InBrowserId,
                                          const FCefFrameId& InFrameId,
                                          const FString& InContext,
                                          const TSharedPtr<FJsonValue>& InResult);

  /// <summary>
  /// Handles the native browser created event from the underlying Slate CEF view.
  /// Used to perform additional initialization after the browser window is available.
  /// </summary>
  void OnSlateNativeBrowserCreatedEvent();

  /// <summary>
  /// Handles the request of creating new browser.
  /// </summary>
  /// <param name="InSourceFrameId">The frame id which requests to create a new browser.</param>
  /// <param name="InUrl">The URL of the new browser.</param>
  /// <param name="InName">The name of the new browser.</param>
  /// <param name="InTargetDisposition">The target disposition of the new browser.</param>
  /// <param name="InRect">The rect of the new browser.</param>
  void OnSlateCreateNewBrowserEvent(const FCefFrameId& InSourceFrameId,
                                    const FString& InUrl,
                                    const FString& InName,
                                    const ECefWindowOpenDisposition& InTargetDisposition,
                                    const FIntRect& InRect);
};
