//
//  Copyright © 2025 SHEEN TECH LAB. All Rights Reserved.
//
//! @file CefContext.h
//! @brief Declares the UCefContext class.
#pragma once

#pragma region <Engine Headers>
// Core/Public/
#include <Containers/UnrealString.h>
#include <Templates/PimplPtr.h>
// CoreUObject/Public/
#include <UObject/ObjectMacros.h>
// Engine/Public/
#include <Subsystems/SubsystemCollection.h>
#include <Subsystems/EngineSubsystem.h>
#pragma endregion

#pragma region <Project Public Headers>
#include <CefSettings.h>
#pragma endregion

#pragma region "Generated Header"
#include "CefContext.generated.h"
#pragma endregion

/// <summary>
/// Represents the Chromium Embedded Framework (CEF) context within Unreal Engine.
/// This class acts as a subsystem, providing centralized access to CEF features such as resource mapping,
/// cookie management, and cross-origin resource sharing (CORS) configuration. All browser instances created
/// after modifying this context will inherit its settings and mappings.
/// </summary>
/// <remarks>
/// UCefContext should be accessed via the engine subsystem interface. It is responsible for initializing and
/// deinitializing CEF resources, and exposes Blueprint-callable methods for common browser integration tasks.
/// </remarks>
UCLASS(BlueprintType)
class UCEFVIEW_API UCefContext : public UEngineSubsystem
{
  GENERATED_BODY()

#pragma region Properties
public:
  /// <summary>
  /// The settings object containing configuration parameters for the CEF context.
  /// This includes options such as cache path, user agent, and other browser-related settings.
  /// </summary>
  /// <remarks>
  /// The Settings property is initialized with the project's mutable default UCefSettings instance.
  /// Modifying these settings affects all subsequently created browser instances.
  /// </remarks>
  UPROPERTY(             //
    BlueprintReadOnly,   //
    Category = "Default" //
  )
  UCefSettings* Settings = GetMutableDefault<UCefSettings>();
#pragma endregion

#pragma region Overrides
protected:
  /// <summary>
  /// Called when the engine subsystem is initialized.
  /// This method sets up the CEF context and prepares it for use by browser instances.
  /// </summary>
  /// <param name="Collection">The subsystem collection used for initialization.</param>
  virtual void Initialize(FSubsystemCollectionBase& Collection) override;

  /// <summary>
  /// Called when the engine subsystem is deinitialized.
  /// This method releases all CEF resources and performs necessary cleanup.
  /// </summary>
  virtual void Deinitialize() override;
#pragma endregion

public:
#pragma region Methods
  /// <summary>
  /// Checks whether the CEF context has been successfully initialized and is ready for use.
  /// </summary>
  /// <returns>
  /// <c>true</c> if the CEF context is initialized and operational; otherwise, <c>false</c>.
  /// </returns>
  /// <remarks>
  /// This method can be used to verify that CEF is available before attempting browser operations.
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool bIsCefInitialized() const;

  /// <summary>
  /// Registers a local folder as a web resource directory, mapping it to a specified URL.
  /// All browser instances created after this call will be able to access the folder's contents via the mapped URL.
  /// </summary>
  /// <param name="InPath">Absolute or relative path to the local resource directory.</param>
  /// <param name="InUrl">The virtual URL to which the directory will be mapped (e.g., "http://myapp.local/").</param>
  /// <param name="InPriority">The priority of the mapping. Higher values take precedence when resolving
  /// resources.</param> <remarks> Use this method to serve static assets (HTML, JS, CSS, etc.) from the local
  /// filesystem to CEF browsers.
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void AddLocalFolderResource(const FString& InPath, const FString& InUrl, int32 InPriority = 0);

  /// <summary>
  /// Registers a local archive file (such as a .zip) as a web resource, mapping its contents to a specified URL.
  /// All browser instances created after this call will be able to access the archive's contents via the mapped URL.
  /// </summary>
  /// <param name="InPath">Absolute or relative path to the local archive file (e.g., .zip).</param>
  /// <param name="InUrl">The virtual URL to which the archive will be mapped.</param>
  /// <param name="InPassword">Password for the archive, if required. Pass an empty string if not needed.</param>
  /// <param name="InPriority">The priority of the mapping. Higher values take precedence.</param>
  /// <remarks>
  /// This is useful for distributing web assets in a compressed format. The archive is mounted read-only.
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void AddArchiveFileResource(const FString& InPath,
                              const FString& InUrl,
                              const FString& InPassword,
                              int32 InPriority = 0);

  /// <summary>
  /// Adds a cookie to the CEF context, this cookie is accessible from all browsers created with this context.
  /// </summary>
  /// <param name="InName">The cookie item name.</param>
  /// <param name="InValue">The cookie item value.</param>
  /// <param name="InDomain">The applicable domain name.</param>
  /// <param name="InUrl">The applicable url.</param>
  /// <returns>True on success; otherwise false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool AddCookie(const FString& InName, const FString& InValue, const FString& InDomain, const FString& InUrl);

  /// <summary>
  /// Deletes all cookies from the CEF context.
  /// </summary>
  /// <returns>True on success; otherwise false.</returns>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool DeleteAllCookies();

  /// <summary>
  /// Adds an entry to the cross-origin access whitelist for the CEF context, allowing specific cross-origin requests
  /// from a given source origin to a target schema and domain. This enables controlled CORS (Cross-Origin Resource
  /// Sharing) behavior for browser instances managed by this context.
  /// </summary>
  /// <param name="InSourceOrigin">
  /// The source origin (e.g., "http://myapp.local") from which cross-origin requests will be allowed.
  /// </param>
  /// <param name="InTargetSchema">
  /// The target schema (e.g., "https") to which cross-origin requests are permitted.
  /// </param>
  /// <param name="InTargetDomain">
  /// The target domain (e.g., "example.com") that will accept cross-origin requests from the source origin.
  /// </param>
  /// <param name="InAllowTargetSubdomains">
  /// If <c>true</c>, subdomains of the target domain are also allowed for cross-origin access.
  /// </param>
  /// <returns>
  /// <c>true</c> if the whitelist entry was successfully added; otherwise, <c>false</c>.
  /// </returns>
  /// <remarks>
  /// Use this method to enable communication between web content hosted in different origins, such as when embedding
  /// local or remote web applications that require access to resources across domains. This is particularly useful
  /// for scenarios involving authentication, APIs, or integration with third-party services.
  /// <para>
  /// Be cautious when granting cross-origin permissions, as this can have security implications. Only allow trusted
  /// origins and domains as needed by your application.
  /// </para>
  /// <para>
  /// If the entry already exists, this method will not add a duplicate. The changes apply to all browser instances
  /// created after the entry is added.
  /// </para>
  /// <para>
  /// For more information, see the CEF documentation:
  /// https://github.com/chromiumembedded/cef/blob/master/include/cef_origin_whitelist.h
  /// </para>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool AddCrossOriginWhitelistEntry(const FString& InSourceOrigin,
                                    const FString& InTargetSchema,
                                    const FString& InTargetDomain,
                                    bool InAllowTargetSubdomains);

  /// <summary>
  /// Removes a specific entry from the cross-origin access whitelist for the CEF context.
  /// This revokes previously granted cross-origin permissions for the specified source and target combination,
  /// enforcing the default CORS policy for affected requests.
  /// </summary>
  /// <param name="InSourceOrigin">The source origin (e.g., "http://myapp.local") for which the whitelist entry was
  /// added.</param> <param name="InTargetSchema">The target schema (e.g., "https") that was allowed for cross-origin
  /// access.</param> <param name="InTargetDomain">The target domain (e.g., "example.com") that was allowed for
  /// cross-origin access.</param> <param name="InAllowTargetSubdomains">Whether subdomains of the target domain were
  /// included in the whitelist entry.</param> <returns> <c>true</c> if the whitelist entry was successfully removed;
  /// otherwise, <c>false</c>.
  /// </returns>
  /// <remarks>
  /// Use this method to dynamically revoke cross-origin permissions previously granted via <see
  /// cref="AddCrossOriginWhitelistEntry"/>. This is useful for tightening security or responding to changes in
  /// application policy at runtime. <para> If the specified entry does not exist, the method returns <c>false</c> and
  /// no changes are made.
  /// </para>
  /// <para>
  /// For more information, see the CEF documentation:
  /// https://github.com/chromiumembedded/cef/blob/master/include/cef_origin_whitelist.h
  /// </para>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  bool RemoveCrossOriginWhitelistEntry(const FString& InSourceOrigin,
                                       const FString& InTargetSchema,
                                       const FString& InTargetDomain,
                                       bool InAllowTargetSubdomains);

  /// <summary>
  /// Removes all entries from the cross-origin access whitelist for the CEF context.
  /// This action revokes any previously granted cross-origin permissions, restoring the default CORS policy.
  /// </summary>
  /// <remarks>
  /// Use this method to reset the CORS configuration for all browser instances managed by this context.
  /// After calling this, any custom cross-origin access rules added via <see cref="AddCrossOriginWhitelistEntry"/>
  /// will be removed, and only the default CEF cross-origin policy will apply.
  /// <para>
  /// This is useful when you need to ensure a clean security state or when dynamically changing the set of allowed
  /// origins.
  /// </para>
  /// <para>
  /// For more information, see the CEF documentation:
  /// https://github.com/chromiumembedded/cef/blob/master/include/cef_origin_whitelist.h
  /// </para>
  /// </remarks>
  UFUNCTION(BlueprintCallable, Category = "Default")
  void ClearCrossOriginWhitelistEntry();
#pragma endregion
};
