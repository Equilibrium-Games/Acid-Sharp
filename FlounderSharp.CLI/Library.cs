﻿using System;
using System.Collections.Generic;
using System.IO;
using CppSharp;
using CppSharp.AST;
using CppSharp.Generators;
using System.Xml.Linq;
using CppSharp.Parser;

namespace FlounderSharp.CLI
{
    class Library : ILibrary
    {
        private string _originalName;
        private string _targetName;
        private List<string> _headerPaths;
        private string _headerFile;
        private string _sharedLibrary;
        private string _libPath;
        private string _outPath;

        private PassXmlTranslation _xmlExportPass;

        public Library(string originalName, string targetName, List<string> headerPaths, string headerFile, string sharedLibrary, string libPath, string outPath)
        {
            _originalName = originalName;
            _targetName = targetName;
            _headerPaths = headerPaths;
            _headerFile = headerFile;
            _sharedLibrary = sharedLibrary;
            _libPath = libPath;
            _outPath = outPath;
            _xmlExportPass = new PassXmlTranslation();
        }


        /// <summary>
        /// Gets the XDocument of the xml representation.
        /// </summary>
        public XDocument XmlExport
        {
            get
            {
                return _xmlExportPass.Document;
            }
        }

        /// <summary>
        /// Sets the driver options. First method called.
        /// </summary>
        /// <param name="driver"></param>
        public void Setup(Driver driver)
        {
            // Sets up the parser.
            var parserOptions = driver.ParserOptions;
            parserOptions.EnableRTTI = true;

            // Sets up other options.
            var options = driver.Options;
            options.OutputDir = _outPath;
            options.GeneratorKind = GeneratorKind.CSharp;
            options.GenerateFinalizers = true;
            options.Verbose = true;

            // Creates a new module.
            var module = options.AddModule(_targetName);
            module.SharedLibraryName = _originalName;
            module.OutputNamespace = "";

        //    module.Defines.Add("FL_BUILD_WINDOWS");
        //    module.Defines.Add("FL_BUILD_MSVC");
        //    module.Defines.Add("FL_EXPORTS");

            module.LibraryDirs.Add(_libPath);

            foreach (var library in Directory.GetFiles(_libPath))
            {
                Console.WriteLine(Path.GetFileName(library));
            //    module.Libraries.Add(library);
            }
            module.Libraries.Add(_sharedLibrary);

            foreach (var path in _headerPaths)
            {
                module.IncludeDirs.Add(path);
            }

            module.Headers.Add(_headerFile);
        }

        /// <summary>
        /// Setup passes. Second method called.
        /// </summary>
        /// <param name="driver"></param>
        public void SetupPasses(Driver driver)
        {
            driver.AddTranslationUnitPass(new PassOutParamsFix());
            driver.AddTranslationUnitPass(_xmlExportPass);
            driver.AddTranslationUnitPass(new PassObjectNamesFix());
            driver.AddTranslationUnitPass(new PassCommentsFix());
        }

        /// <summary>
        /// Do transformations that should happen before any passes are processed.
        /// </summary>
        /// <param name="driver"></param>
        /// <param name="ctx"></param>
        public void Preprocess(Driver driver, ASTContext ctx)
        {
        }

        /// <summary>
        /// Do transformations that should happen after all passes are processed.
        /// </summary>
        /// <param name="driver"></param>
        /// <param name="ctx"></param>
        public void Postprocess(Driver driver, ASTContext ctx)
        {
        }
    }
}