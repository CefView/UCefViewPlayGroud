//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file SlateCefContext.h
//! @brief Declares the FSlateCefContext class, a Slate class that represents the CEF context.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/UnrealString.h>
#include <Templates/PimplPtr.h>
#pragma endregion

#pragma region <Project Public Headers>
#include <CefViewTypes.h>
#include <Slate/SlateCefSettings.h>
#pragma endregion

/// <summary>
/// Manages the Chromium Embedded Framework (CEF) context for Slate-based UI components.
/// Provides global resource mapping, cookie management, and cross-origin whitelist control
/// for all SCefView instances created in the application.
/// </summary>
class UCEFVIEW_API FSlateCefContext
{
  friend class SCefViewPrivate;

  class FSlateCefContextPrivate;
  /// <summary>
  /// Pointer to the private implementation of FSlateCefContext.
  /// Used to hide implementation details and reduce compile-time dependencies.
  /// </summary>
  TPimplPtr<FSlateCefContextPrivate> m_pImp;

private:
  /// <summary>
  /// Holds the current global CEF context instance.
  /// </summary>
  static TSharedPtr<FSlateCefContext> CurrentContext;

  /// <summary>
  /// Constructs a new FSlateCefContext instance.
  /// Private to enforce singleton pattern.
  /// </summary>
  FSlateCefContext();

public:
  /// <summary>
  /// Destructor. Cleans up and releases all resources held by the CEF context.
  /// </summary>
  ~FSlateCefContext();

  /// <summary>
  /// Creates and initializes the global CEF context with the specified settings.
  /// If a context already exists, this call has no effect.
  /// </summary>
  /// <param name="InSettings">CEF context settings to use for initialization.</param>
  static void Create(const FSlateCefSettings& InSettings);

  /// <summary>
  /// Shuts down and destroys the global CEF context, releasing all associated resources.
  /// After shutdown, the context must be re-created before use.
  /// </summary>
  static void Shutdown();

  /// <summary>
  /// Checks if the CEF context has been initialized and is available for use.
  /// </summary>
  /// <returns>True if the context is initialized; otherwise, false.</returns>
  static bool IsInitialized();

  /// <summary>
  /// Gets a reference to the current global CEF context instance.
  /// Throws if the context is not initialized.
  /// </summary>
  /// <returns>Reference to the current FSlateCefContext.</returns>
  static FSlateCefContext& Get();

public:
  /// <summary>
  /// Adds a URL mapping for a local web resource directory.
  /// All subsequently created SCefView instances will be able to access resources in this directory via the specified
  /// URL.
  /// </summary>
  /// <param name="InPath">The absolute path to the local resource directory.</param>
  /// <param name="InUrl">The virtual URL to map to the directory (e.g., "http://local/").</param>
  /// <param name="InPriority">The priority of the mapping. Higher values take precedence. Default is 0.</param>
  void AddLocalFolderResource(const FString& InPath, const FString& InUrl, int32 InPriority = 0);

  /// <summary>
  /// Adds a URL mapping for a local archive (.zip) file containing web resources.
  /// All subsequently created SCefView instances will be able to access resources in this archive via the specified
  /// URL.
  /// </summary>
  /// <param name="InPath">The absolute path to the local archive file.</param>
  /// <param name="InUrl">The virtual URL to map to the archive (e.g., "http://archive/").</param>
  /// <param name="InPassword">The password required to access the archive, if any.</param>
  /// <param name="InPriority">The priority of the mapping. Higher values take precedence. Default is 0.</param>
  void AddArchiveFileResource(const FString& InPath,
                              const FString& InUrl,
                              const FString& InPassword,
                              int32 InPriority = 0);

  /// <summary>
  /// Adds a cookie to the CEF context. The cookie will be accessible from all browsers created with this context.
  /// </summary>
  /// <param name="InName">The name of the cookie.</param>
  /// <param name="InValue">The value of the cookie.</param>
  /// <param name="InDomain">The domain to which the cookie applies.</param>
  /// <param name="InUrl">The URL to which the cookie applies.</param>
  /// <returns>True if the cookie was successfully added; otherwise, false.</returns>
  bool AddCookie(const FString& InName, const FString& InValue, const FString& InDomain, const FString& InUrl);

  /// <summary>
  /// Deletes all cookies from the CEF context.
  /// </summary>
  /// <returns>True if all cookies were successfully deleted; otherwise, false.</returns>
  bool DeleteAllCookies();

  /// <summary>
  /// Adds an entry to the cross-origin access whitelist, allowing requests from a source origin to a target
  /// domain/schema. For more details, see:
  /// https://github.com/chromiumembedded/cef/blob/605c2bac86415dcec1e2902cdc46dc11c1ad026a/include/cef_origin_whitelist.h#L81C23-L81C23
  /// </summary>
  /// <param name="InSourceOrigin">The source origin (e.g., "http://example.com").</param>
  /// <param name="InTargetSchema">The target schema (e.g., "http").</param>
  /// <param name="InTargetDomain">The target domain (e.g., "target.com").</param>
  /// <param name="InAllowTargetSubdomains">True to allow subdomains of the target domain; otherwise, false.</param>
  /// <returns>True if the whitelist entry was successfully added; otherwise, false.</returns>
  bool AddCrossOriginWhitelistEntry(const FString& InSourceOrigin,
                                    const FString& InTargetSchema,
                                    const FString& InTargetDomain,
                                    bool InAllowTargetSubdomains);

  /// <summary>
  /// Removes an entry from the cross-origin access whitelist.
  /// For more details, see:
  /// https://github.com/chromiumembedded/cef/blob/605c2bac86415dcec1e2902cdc46dc11c1ad026a/include/cef_origin_whitelist.h#L91C12-L91C12
  /// </summary>
  /// <param name="InSourceOrigin">The source origin (e.g., "http://example.com").</param>
  /// <param name="InTargetSchema">The target schema (e.g., "http").</param>
  /// <param name="InTargetDomain">The target domain (e.g., "target.com").</param>
  /// <param name="InAllowTargetSubdomains">True to allow subdomains of the target domain; otherwise, false.</param>
  /// <returns>True if the whitelist entry was successfully removed; otherwise, false.</returns>
  bool RemoveCrossOriginWhitelistEntry(const FString& InSourceOrigin,
                                       const FString& InTargetSchema,
                                       const FString& InTargetDomain,
                                       bool InAllowTargetSubdomains);

  /// <summary>
  /// Removes all entries from the cross-origin access whitelist for the current context.
  /// </summary>
  void ClearCrossOriginWhitelistEntry();
};
