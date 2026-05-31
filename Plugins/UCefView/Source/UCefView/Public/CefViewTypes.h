//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file CefViewTypes.h
//! @brief Declares core types and structures used by the UCefView plugin.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/UnrealString.h>
#include <HAL/Platform.h>
// CoreUObject/Public/
#include <UObject/ObjectMacros.h>
#pragma endregion

#pragma region <Project Public Headers>
#include <CefVersion.h>
#pragma endregion

#pragma region "Generated Header"
#include "CefViewTypes.generated.h"
#pragma endregion

/// <summary>
/// Type alias for CEF frame id, used to uniquely identify a browser frame within the Chromium Embedded Framework.
/// </summary>
/// <remarks>
/// <para>
/// The underlying type of the frame id depends on the CEF version: for versions prior to 122, it is an integer; for 122
/// and above, it is a string.
/// </para>
/// <para>
/// This struct is used throughout the UCefView plugin to reference specific frames for navigation, scripting, and event
/// handling.
/// </para>
/// </remarks>
/// <example>
/// <code>
/// FCefFrameId FrameId(12345); // For CEF < 122
/// FCefFrameId FrameId(TEXT("frame-guid")); // For CEF >= 122
/// </code>
/// </example>
USTRUCT(BlueprintType)
struct UCEFVIEW_API FCefFrameId
{
  GENERATED_BODY()

  /// <summary>
  /// Default constructor for FCefFrameId. Initializes the frame id to zero (for int) or empty string (for FString).
  /// </summary>
  FCefFrameId() {}

#if CEF_VERSION_MAJOR < 122
  /// <summary>
  /// Constructor for FCefFrameId with an integer id.
  /// </summary>
  /// <param name="Id">The integer id to initialize the frame id. Typically provided by CEF for frame
  /// identification.</param>
  FCefFrameId(int64 Id)
    : Value(Id)
  {
  }

  /// <summary>
  /// The integer value representing the frame id.
  /// </summary>
  /// <remarks>
  /// Used for CEF versions prior to 122. This value is unique within the browser process.
  /// </remarks>
  int64 Value = 0;
#else
  /// <summary>
  /// Constructor for FCefFrameId with a string id.
  /// </summary>
  /// <param name="Id">The string id to initialize the frame id. Typically a GUID or unique string provided by
  /// CEF.</param>
  FCefFrameId(const TCHAR* Id)
    : Value(Id)
  {
  }

  /// <summary>
  /// The string value representing the frame id.
  /// </summary>
  /// <remarks>
  /// Used for CEF versions 122 and above. This value is globally unique.
  /// </remarks>
  FString Value = TEXT("");
#endif
};

/// <summary>
/// Represents the possible states of a CEF view feature, such as enabling or disabling specific browser capabilities.
/// </summary>
/// <remarks>
/// Use this enum to control the activation state of features like JavaScript, plugins, or popups in the CEF view.
/// </remarks>
UENUM(BlueprintType)
enum class ECefViewFeatureState : uint8
{
  /// <summary>
  /// Default state. The feature uses the default setting as determined by CEF or the application.
  /// </summary>
  Default = 0,

  /// <summary>
  /// Enabled state. The feature is explicitly enabled.
  /// </summary>
  Enabled = 1,

  /// <summary>
  /// Disabled state. The feature is explicitly disabled.
  /// </summary>
  Disabled = 2,
};

/// <summary>
/// Represents the CEF pop-up windows open disposition, determining how new windows or tabs are handled.
/// </summary>
/// <remarks>
/// This enum is used to specify the target for content that requests to open in a new window or tab, such as from
/// JavaScript window.open() calls or link targets.
/// </remarks>
UENUM(BlueprintType)
enum class ECefWindowOpenDisposition : uint8
{
  /// <summary>
  /// Unknown disposition. The target is not specified or cannot be determined.
  /// </summary>
  Unknown,

  /// <summary>
  /// Current Tab: Opens the content in the current tab or window, replacing the existing content.
  /// </summary>
  CurrentTab,

  /// <summary>
  /// Singleton Tab: Opens the content in a singleton tab, ensuring only one instance exists.
  /// </summary>
  SingletonTab,

  /// <summary>
  /// New Foreground Tab: Opens the content in a new tab in the foreground, giving it focus.
  /// </summary>
  NewForeGroundTab,

  /// <summary>
  /// New Background Tab: Opens the content in a new tab in the background, without focus.
  /// </summary>
  NewBackgroundTab,

  /// <summary>
  /// New Popup: Opens the content in a new popup window, typically with limited UI.
  /// </summary>
  NewPopup,

  /// <summary>
  /// New Window: Opens the content in a new top-level window.
  /// </summary>
  NewWindow,

  /// <summary>
  /// Save To Disk: Downloads the content to disk instead of displaying it.
  /// </summary>
  SaveToDisk,

  /// <summary>
  /// Off The Record: Opens the content in off-the-record mode (incognito/private browsing).
  /// </summary>
  OffTheRecord,

  /// <summary>
  /// Ignore Action: Ignores the open disposition and prevents the action.
  /// </summary>
  IgnoreAction,
};

/// <summary>
/// Represents a mapping from a local folder to a URL for resource loading in the CEF browser.
/// </summary>
/// <remarks>
/// <para>
/// This struct is used to expose static assets (such as HTML, JavaScript, CSS, images) from a local directory to the
/// browser via a virtual URL.
/// </para>
/// <para>
/// The mapping allows the browser to load resources as if they were hosted remotely, enabling offline or packaged web
/// applications.
/// </para>
/// </remarks>
/// <example>
/// <code>
/// FLocalFolderResourceMapping Mapping;
/// Mapping.Url = TEXT("http://myapp.local/");
/// Mapping.Path.Path = TEXT("WebAssets");
/// Mapping.Priority = 1;
/// </code>
/// </example>
USTRUCT(BlueprintType)
struct UCEFVIEW_API FLocalFolderResourceMapping
{
  GENERATED_BODY()

  /// <summary>
  /// The target URL to be mapped to.
  /// </summary>
  /// <remarks>
  /// This is the virtual URL that the browser will use to access resources from the specified local folder.
  /// Example: "http://myapp.local/"
  /// </remarks>
  UPROPERTY(EditAnywhere,        //
            BlueprintReadWrite,  //
            Category = "Default" //
  )
  FString Url;

  /// <summary>
  /// The folder containing the resources to be mapped.
  /// </summary>
  /// <remarks>
  /// The path value must be relative to the game content directory (e.g., "WebAssets").
  /// All files within this folder will be accessible via the specified Url.
  /// </remarks>
  UPROPERTY(EditAnywhere,                     //
            BlueprintReadWrite,               //
            Category = "Default",             //
            meta = (RelativeToGameContentDir) //
  )
  FDirectoryPath Path;

  /// <summary>
  /// The priority of the mapping.
  /// </summary>
  /// <remarks>
  /// Higher priority mappings take precedence when multiple mappings overlap.
  /// </remarks>
  UPROPERTY(EditAnywhere,        //
            BlueprintReadWrite,  //
            Category = "Default" //
  )
  int32 Priority = 0;

  /// <summary>
  /// Equality operator for comparing two FLocalFolderResourceMapping objects.
  /// </summary>
  /// <param name="Other">The other mapping to compare with.</param>
  /// <returns>True if the mappings are equal, false otherwise.</returns>
  /// <remarks>
  /// Two mappings are considered equal if their Url, Path, and Priority are all identical.
  /// </remarks>
  bool operator==(const FLocalFolderResourceMapping& Other) const
  {
    return (true                            //
            && Url == Other.Url             //
            && Path.Path == Other.Path.Path //
            && Priority == Other.Priority   //
    );
  }

  /// <summary>
  /// Inequality operator for comparing two FLocalFolderResourceMapping objects.
  /// </summary>
  /// <param name="Other">The other mapping to compare with.</param>
  /// <returns>True if the mappings are not equal, false otherwise.</returns>
  /// <remarks>
  /// Returns true if any of the Url, Path, or Priority fields differ.
  /// </remarks>
  bool operator!=(const FLocalFolderResourceMapping& Other) const
  {
    //
    return !(*this == Other);
  }
};

/// <summary>
/// Represents a mapping from an archive file (zip) to a URL for resource loading in the CEF browser.
/// </summary>
/// <remarks>
/// <para>
/// This struct allows you to serve web assets from a compressed archive file, making distribution and packaging easier.
/// The browser can access files inside the archive as if they were hosted at the specified Url.
/// </para>
/// </remarks>
/// <example>
/// <code>
/// FArchiveFileResourceMapping Mapping;
/// Mapping.Url = TEXT("http://archive.local/");
/// Mapping.Path.FilePath = TEXT("WebAssets.zip");
/// Mapping.Password = TEXT("secret");
/// Mapping.Priority = 2;
/// </code>
/// </example>
USTRUCT(BlueprintType)
struct UCEFVIEW_API FArchiveFileResourceMapping
{
  GENERATED_BODY()

  /// <summary>
  /// The target URL to be mapped to.
  /// </summary>
  /// <remarks>
  /// This is the virtual URL that the browser will use to access resources from the specified archive file.
  /// Example: "http://archive.local/"
  /// </remarks>
  UPROPERTY(EditAnywhere,        //
            BlueprintReadWrite,  //
            Category = "Default" //
  )
  FString Url;

  /// <summary>
  /// The zip format file containing the resources to be mapped.
  /// </summary>
  /// <remarks>
  /// The path value must be relative to the game directory (e.g., "WebAssets.zip").
  /// Only zip archives are supported.
  /// </remarks>
  UPROPERTY(EditAnywhere,              //
            BlueprintReadWrite,        //
            Category = "Default",      //
            meta = (RelativeToGameDir) //
  )
  FFilePath Path;

  /// <summary>
  /// The password for accessing the archive file, if required.
  /// </summary>
  /// <remarks>
  /// Leave empty if the archive is not password-protected.
  /// </remarks>
  UPROPERTY(EditAnywhere,        //
            BlueprintReadWrite,  //
            Category = "Default" //
  )
  FString Password;

  /// <summary>
  /// The priority of the mapping.
  /// </summary>
  /// <remarks>
  /// Higher priority mappings take precedence when multiple mappings overlap.
  /// </remarks>
  UPROPERTY(EditAnywhere,        //
            BlueprintReadWrite,  //
            Category = "Default" //
  )
  int32 Priority = 0;

  /// <summary>
  /// Equality operator for comparing two FArchiveFileResourceMapping objects.
  /// </summary>
  /// <param name="Other">The other mapping to compare with.</param>
  /// <returns>True if the mappings are equal, false otherwise.</returns>
  /// <remarks>
  /// Two mappings are considered equal if their Url, Path, Password, and Priority are all identical.
  /// </remarks>
  bool operator==(const FArchiveFileResourceMapping& Other) const
  {
    return (true                                    //
            && Url == Other.Url                     //
            && Path.FilePath == Other.Path.FilePath //
            && Password == Other.Password           //
            && Priority == Other.Priority           //
    );
  }

  /// <summary>
  /// Inequality operator for comparing two FArchiveFileResourceMapping objects.
  /// </summary>
  /// <param name="Other">The other mapping to compare with.</param>
  /// <returns>True if the mappings are not equal, false otherwise.</returns>
  /// <remarks>
  /// Returns true if any of the Url, Path, Password, or Priority fields differ.
  /// </remarks>
  bool operator!=(const FArchiveFileResourceMapping& Other) const
  {
    //
    return !(*this == Other);
  }
};
